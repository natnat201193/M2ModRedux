#pragma once
#include "M2.h"
#include <set>
#include <unordered_map>

namespace M2Lib
{
	namespace BoneComparator
	{
		enum class CompareStatus
		{
			Identical = 0,
			IdenticalWithinThreshold = 1,
			Differ = 2,
		};

		class Candidates
		{
		public:
			void AddCandidate(uint32_t BoneId);

			std::unordered_map<uint32_t, float> GetWeightedCandidates();

			uint32_t Size() const { return BoneUsage.size(); }

		private:
			std::unordered_map<uint32_t, uint32_t> BoneUsage;
		};

		typedef std::unordered_map<uint32_t /*BoneId*/, std::unordered_map<uint32_t /*BoneId*/, float /*Probability*/>> WeightedDifferenceMap;

		struct DiffResult
		{
			WeightedDifferenceMap map;
			float matchedPercent;
		};
		
		DiffResult Diff(M2 const* oldM2, M2 const* newM2, bool CompareTextures, bool predictScale, float& sourceScale);

		CompareStatus GetDifferenceStatus(WeightedDifferenceMap const& WeightedResult, float weightThreshold);

		M2LIB_API M2LIB_HANDLE __cdecl Wrapper_Create(M2LIB_HANDLE oldM2, M2LIB_HANDLE newM2, float weightThreshold, bool compareTextures, bool predictScale, float& sourceScale);
		M2LIB_API CompareStatus __cdecl Wrapper_GetResult(M2LIB_HANDLE pointer);
		M2LIB_API const wchar_t* __cdecl Wrapper_GetStringResult(M2LIB_HANDLE pointer);
		M2LIB_API uint32_t __cdecl Wrapper_DiffSize(M2LIB_HANDLE pointer);
		M2LIB_API void __cdecl Wrapper_Free(M2LIB_HANDLE pointer);

		class ComparatorWrapper
		{
		public:
			ComparatorWrapper(M2 const* oldM2, M2 const* newM2, float weightThreshold, bool compareTextures, bool predictScale, float& sourceScale);
			~ComparatorWrapper() = default;
			
			CompareStatus GetResult() const;
			const wchar_t* GetStringResult() const;
			uint32_t DiffSize() const;
			
		private:
			CompareStatus compareStatus;
			WeightedDifferenceMap diffMap;
			std::wstring buffer;
		};
	}
}
