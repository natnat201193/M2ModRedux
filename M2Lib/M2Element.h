#pragma once

#include "BaseTypes.h"
#include "M2Types.h"

namespace M2Lib
{
	namespace M2Element
	{
		// named indices.
		enum EElement
		{
			EElement_Name = 0,
			EElement_GlobalSequence = 1,
			EElement_Animation = 2,
			EElement_AnimationLookup = 3,
			EElement_Bone = 4,
			EElement_KeyBoneLookup = 5,
			EElement_Vertex = 6,
			EElement_Color = 7,
			EElement_Texture = 8,
			EElement_Transparency = 9,
			EElement_TextureAnimation = 10,
			EElement_TextureReplace = 11,
			EElement_TextureFlags = 12,
			EElement_SkinnedBoneLookup = 13,
			EElement_TextureLookup = 14,
			EElement_TextureUnitLookup = 15,
			EElement_TransparencyLookup = 16,
			EElement_TextureAnimationLookup = 17,
			EElement_BoundingTriangle = 18,
			EElement_BoundingVertex = 19,
			EElement_BoundingNormal = 20,
			EElement_Attachment = 21,
			EElement_AttachmentLookup = 22,
			EElement_Event = 23,
			EElement_Light = 24,
			EElement_Camera = 25,
			EElement_CameraLookup = 26,
			EElement_RibbonEmitter = 27,
			EElement_ParticleEmitter = 28,
			EElement_TextureCombinerCombo = 29,

			EElement__Count__
		};

#pragma pack(push, 1)
		//
		//
		class CElement_Name
		{
		public:
			Char8* szName;

		public:
			CElement_Name()
			{
				szName = 0;
			}

			~CElement_Name()
			{
				if (szName)
				{
					delete[] szName;
				}
			}
		};


		//
		//
		class CElement_GlobalSequence
		{
		public:
			UInt32 Value;
		};

		class CElement_AnimationLookup
		{
		public:
			UInt16 AnimationID;
		};

		ASSERT_SIZE(CElement_GlobalSequence, 4);

		//
		// some sort of animation entry (without any apparent referenced animation data).
		class CElement_Animation
		{
		public:
			UInt16 AnimationID;
			UInt16 AnimationSubID;
			UInt32 Length;

			Float32 MoveSpeed;

			UInt32 Flags;

			SInt16 Rarity;

			UInt16 Padding;
			UInt32 BlendTimeIn;
			UInt32 BlendTimeOut;

			UInt32 PlaySpeed;

			SVolume BoundingVolume;

			SInt16 NextAnimation;		// index to next animation with same AnimationID, -1 if there are no more.
			UInt16 NextIndex;			// this animation's index in the list of animations.

			bool IsInline() const { return (Flags & 0x20) != 0; }
		};

		ASSERT_SIZE(CElement_Animation, 64);

		//
		// generic animation block header.
		class CElement_AnimationBlock
		{
		public:
			// an animation will reference several of these, and each of these in turn corresponds to a bone (my best guess).
			class CChannel
			{
			public:
				UInt32 n;	// number
				UInt32 o;	// offset
			};

			// used for times?
			struct SKey_UInt32
			{
				UInt32 Values[1];
			};

			// used for position and scale keys.
			struct SKey_Float32x3
			{
				Float32 Values[3];
			};

			// used for rotation quaternion keys.
			struct SKey_SInt16x4
			{
				UInt16 Values[4];
			};

			// used for visibility, probably interpreted as boolean.
			struct SKey_UInt16
			{
				UInt16 Values[1];
			};

			// used for light intensity, etc.
			struct SKey_Float32
			{
				Float32 Values[1];
			};

			enum EInterpolationType
				: UInt16
			{
				EInterpolationType_None = 0,
				EInterpolationType_Linear = 1,
				EInterpolationType_Hermite = 2,
			};

		public:

			CElement_AnimationBlock()
			{
				InterpolationType = EInterpolationType_None;
				GlobalSequenceID = -1;
			}

			EInterpolationType InterpolationType;
			SInt16 GlobalSequenceID;
			M2Array Times;
			M2Array Keys;
		};

		ASSERT_SIZE(CElement_AnimationBlock, 20);

		class CElement_FakeAnimationBlock
		{
		public:
			M2Array Times;
			M2Array Keys;
		};

		ASSERT_SIZE(CElement_FakeAnimationBlock, 16);

		//
		// a list of these makes up a skeleton.
		class CElement_Bone
		{
		public:
			enum EFlags
				: UInt32
			{
				EFlags_SphericalBillboard = 0x8,
				EFlags_BilboardLockX = 0x10,
				EFlags_BilboardLockY = 0x20,
				EFlags_BilboardLockZ = 0x40,
				EFlags_Transformed = 0x200,
				EFlags_Kinematic = 0x400,		// MoP+: allow physics to influence this bone
				EFlags_AnimScaled = 0x1000,		// set blend_modificator to helmetAnimScalingRec.m_amount for this bone
			};

		public:
			SInt32 BoneLookupID;		// index into BoneLookup table or -1.
			EFlags Flags;				//
			SInt16 ParentBone;			// index to parent bone or -1.
			UInt16 SubmeshId;			// // Mesh part ID
			UInt16 Unknown[2];			// ?
			CElement_AnimationBlock AnimationBlock_Position;	// Float32x3
			CElement_AnimationBlock AnimationBlock_Rotation;	// SInt16x4
			CElement_AnimationBlock AnimationBlock_Scale;		// Float32x3
			C3Vector Position;
		};

		ASSERT_SIZE(CElement_Bone, 88);

		//
		//
		class CElement_BoneLookup
		{
		public:
			enum EBoneLookup
				: SInt16
			{
				EBoneLookup_ArmL,
				EBoneLookup_ArmR,
				EBoneLookup_ShoulderL,
				EBoneLookup_ShoulderR,
				EBoneLookup_SpineLow,
				EBoneLookup_Waist,
				EBoneLookup_Head,
				EBoneLookup_Jaw,
				EBoneLookup_IndexFingerR,
				EBoneLookup_MiddleFingerR,
				EBoneLookup_PinkyFingerR,
				EBoneLookup_RingFingerR,
				EBoneLookup_ThumbR,
				EBoneLookup_IndexFingerL,
				EBoneLookup_MiddleFingerL,
				EBoneLookup_PinkyFingerL,
				EBoneLookup_RingFingerL,
				EBoneLookup_ThumbL,
				EBoneLookup_Event_BTH,
				EBoneLookup_Event_CSR,
				EBoneLookup_Event_CSL,
				EBoneLookup_Breath,
				EBoneLookup_Name,
				EBoneLookup_NameMount,
				EBoneLookup_Event_CHD,
				EBoneLookup_Event_CCH,
				EBoneLookup_Root,
				EBoneLookup_Wheel1,
				EBoneLookup_Wheel2,
				EBoneLookup_Wheel3,
				EBoneLookup_Wheel4,
				EBoneLookup_Wheel5,
				EBoneLookup_Wheel6,
				EBoneLookup_Wheel7,
				EBoneLookup_Wheel8,
			};

		public:
			EBoneLookup BoneLookup;
		};

		ASSERT_SIZE(CElement_BoneLookup, 2);

		//
		//
		class CElement_Color
		{
		public:
			CElement_AnimationBlock AnimationBlock_Color;		// Float32x3
			CElement_AnimationBlock AnimationBlock_Opacity;		// UInt16
		};

		ASSERT_SIZE(CElement_Color, 40);

		//
		//
		class CElement_Texture
		{
		public:
			enum class ETextureType
				: UInt32
			{
				Final_Hardcoded = 0,
				Skin = 1,
				ObjectSkin = 2,
				WeaponBlade = 3,
				WeaponHandle = 4,
				Environment = 5,
				Hair = 6,
				FacialHair = 7,
				SkinExtra = 8,
				UiSkin = 9,
				TaurenMane = 10,
				Monster1 = 11,
				Monster2 = 12,
				Monster3 = 13,
				ItemIcon = 14,
				GuildBackgroundColor = 15,
				GuildEmblemColor = 16,
				GuildBorderColor = 17,
				GuildEmblem = 18
			};

			static std::string GetTypeString(ETextureType Type);

			enum class ETextureFlags
				: UInt32
			{
				None = 0,
				WrapX = 1,
				WrapY = 2
			};

			ETextureType Type;
			ETextureFlags Flags;
			M2Array TexturePath;	// texture
		};

		ASSERT_SIZE(CElement_Texture, 16);

		//
		//
		class CElement_Transparency
		{
		public:
			CElement_AnimationBlock AnimationBlock_Transparency;	// UInt16

		};

		ASSERT_SIZE(CElement_Transparency, 20);

		//
		// texture coordinate animation block.
		class CElement_UVAnimation
		{
		public:
			CElement_AnimationBlock AnimationBlock_Position;	// Float32x3
			CElement_AnimationBlock AnimationBlock_Rotation;	// SInt16x4
			CElement_AnimationBlock AnimationBlock_Scale;		// Float32x3
		};

		ASSERT_SIZE(CElement_UVAnimation, 60);

		//
		//
		class CElement_TextureReplace
		{
		public:
			SInt16 TextureID;
		};

		ASSERT_SIZE(CElement_TextureReplace, 2);

		//
		//
		class CElement_TextureFlag
		{
		public:
			enum EFlags
				: UInt16
			{
				EFlags_None = 0x00,
				EFlags_Unlit = 0x01,
				EFlags_Unfogged = 0x02,
				EFlags_TwoSided = 0x04,
				EFlags_Billboard = 0x08,
				EFlags_NoZBuffer = 0x10,
				EFlags_Unk6 = 0x40, // shadow batch related
				EFlags_Unk7 = 0x80, // shadow batch related
				EFlags_Unk8 = 0x400, // wod
				EFlags_Unk9 = 0x800, // prevent alpha for custom elements. if set, use (fully) opaque or transparent. (litSphere, shadowMonk) (MoP+) 
			};

			enum EBlend : UInt16
			{
				EBlend_Opaque = 0,
				EBlend_Mod,
				EBlend_Decal,
				EBlend_Add,
				EBlend_Mod2x,
				EBlend_Fade,
				EBlend_Unknown6,
				EBlend_Unknown7
			};

		public:
			EFlags Flags;
			EBlend Blend;
		};

		ASSERT_SIZE(CElement_TextureFlag, 4);

		//
		// each skin file has one or more bone partitions. each bone partition references into a subset of this skinned bone lookup array.
		class CElement_PartitionedBoneLookup
		{
		public:
			UInt16 BoneIndex;			// index into the model's bone list.
		};

		ASSERT_SIZE(CElement_PartitionedBoneLookup, 2);

		//
		//
		class CElement_TextureLookup
		{
		public:
			UInt16 TextureIndex;
		};

		ASSERT_SIZE(CElement_TextureLookup, 2);

		//
		//
		class CElement_TextureUnits
		{
		public:
			UInt16 Unit;
		};

		ASSERT_SIZE(CElement_TextureUnits, 2);

		//
		//
		class CElement_TransparencyLookup
		{
		public:
			UInt16 TransparencyLookup;
		};

		ASSERT_SIZE(CElement_TransparencyLookup, 2);

		//
		//
		class CElement_UVAnimationLookup
		{
		public:
			UInt16 TextureIndex;
		};

		ASSERT_SIZE(CElement_UVAnimationLookup, 2);

		//
		//
		class CElement_BoundingTriangle
		{
		public:
			UInt16 Index;
		};

		ASSERT_SIZE(CElement_BoundingTriangle, 2);

		//
		//
		class CElement_BoundingVertices
		{
		public:
			C3Vector Position;
		};

		ASSERT_SIZE(CElement_BoundingVertices, 12);

		//
		//
		class CElement_BoundingNormals
		{
		public:
			C3Vector Normal;
		};

		ASSERT_SIZE(CElement_BoundingNormals, 12);

		//
		// an attachment to a bone defines where items and effects will anchor to the rig.
		class CElement_Attachment
		{
		public:
			enum EID
				: UInt32
			{
				EID_WristL = 0,		// (shield)
				EID_PalmR = 1,
				EID_PalmL = 2,
				EID_ElbowR = 3,
				EID_ElbowL = 4,
				EID_ShoulderR = 5,
				EID_ShoulderL = 6,
				EID_KneeR = 7,
				EID_KneeL = 8,
				EID_HipR = 9,
				EID_HipL = 10,
				EID_Helmet = 11,
				EID_Back = 12,
				EID_ShoulderFlapR = 13,
				EID_ShoulderFlapL = 14,
				EID_ChestBloodFront = 15,
				EID_ChestBloodBack = 16,
				EID_Breath = 17,
				EID_PlayerName = 18,
				EID_Base = 19,
				EID_Head = 20,
				EID_SpellHandL = 21,
				EID_SpellHandR = 22,
				EID_Special1 = 23,
				EID_Special2 = 24,
				EID_Special3 = 25,
				EID_BackWeaponR = 26,
				EID_BackWeaponL = 27,
				EID_BackSheathShield = 28,
				EID_PlayerNameMounted = 29,
				EID_LargeWeaponL = 30,
				EID_LargeWeaponR = 31,
				EID_HipWeaponL = 32,
				EID_HipWeaponR = 33,
				EID_Chest = 34,
				EID_HandArrow = 35,
				EID_Bullet = 36,
				EID_SpellHandOmni = 37,
				EID_SpellHandDirected = 38,
				EID_VechicleSeat1 = 39,
				EID_VechicleSeat2 = 40,
				EID_VechicleSeat3 = 41,
				EID_VechicleSeat4 = 42,
				EID_VechicleSeat5 = 43,
				EID_VechicleSeat6 = 44,
				EID_VechicleSeat7 = 45,
				EID_VechicleSeat8 = 46,
				EID_FootL = 47,
				EID_FootR = 48,
				EID_ShieldNoGlove = 49,
				EID_SpineLow = 50,
				EID_AlteredShoulderR = 51,
				EID_AlteredSoulderL = 52,
				EID_BeltBuckle = 53,
				EID_SheathCrossbow = 54,
				EID_HeadTop = 55	// horns?
			};

		public:
			UInt32 ID;					//
			UInt32 ParentBone;			// parent bone.
			C3Vector Position;			// position relative to parent bone.
			CElement_AnimationBlock AnimationBlock_Visibility;	// UInt16.
		};

		ASSERT_SIZE(CElement_Attachment, 40);

		//
		//
		class CElement_AttachmentLookup
		{
		public:
			enum EAttachmentLookup : UInt16
			{
				EAttachmentLookup_Item_PalmR,
				EAttachmentLookup_Item_PalmL,
				EAttachmentLookup_Item_ElbowR,
				EAttachmentLookup_Item_ElbowL,
				EAttachmentLookup_Item_ShoulderR,
				EAttachmentLookup_Item_ShoulderL,
				EAttachmentLookup_Item_KneeR,
				EAttachmentLookup_Item_KneeL,
				EAttachmentLookup_Item_HipR,
				EAttachmentLookup_Item_HipL,
				EAttachmentLookup_Item_Helmet,
				EAttachmentLookup_Item_Back,
				EAttachmentLookup_Item_ShoulderExtR,
				EAttachmentLookup_Item_ShoulderExtL,
				EAttachmentLookup_Hit_Front,
				EAttachmentLookup_Hit_Back,
				EAttachmentLookup_Spell_Mouth,
				EAttachmentLookup_Spell_NearHead,
				EAttachmentLookup_Spell_Base,
				EAttachmentLookup_Spell_Head,
				EAttachmentLookup_Spell_Precast1L,
				EAttachmentLookup_Spell_Precast1R,
				EAttachmentLookup_Spell_Precast2L,
				EAttachmentLookup_Spell_Precast2R,
				EAttachmentLookup_Spell_Precast3,
				EAttachmentLookup_Sheath_UpBackR,
				EAttachmentLookup_Sheath_UpBackL,
				EAttachmentLookup_Sheath_CenterBack,
				EAttachmentLookup_Sheath_HipBelly,
				EAttachmentLookup_Sheath_UpDownBack,
				EAttachmentLookup_Sheath_UnknownBack,
				EAttachmentLookup_Sheath_HipL,
				EAttachmentLookup_Sheath_HipR,
				EAttachmentLookup_Sheath_Chest,
				EAttachmentLookup_Unknown_PalmR1,
				EAttachmentLookup_Unknown_PalmR2,
			};

		public:
			EAttachmentLookup AttachmentLookup;

		};

		ASSERT_SIZE(CElement_AttachmentLookup, 2);


		//
		// events define sounds that are played during animation.
		class CElement_Event
		{
		public:
			class CTimeLine
			{
			public:
				UInt32 nTimeStamps;
				UInt32 oTimeStamps;
			};

		public:
			Char8 ID[4];			// this event's ID.
			UInt32 SoundID;			// database id of sound to play from SoundEntries.dbc.
			UInt32 ParentBone;		// parent bone.
			C3Vector Position;		// position relative to parent bone.
			UInt16 InterpolationType;
			SInt16 GlobalSequenceID;
			M2Array TimeLines;
		};

		ASSERT_SIZE(CElement_Event, 36);

		//
		//
		class CElement_Light
		{
		public:
			UInt16 Type;
			UInt16 ParentBone;
			C3Vector Position;
			CElement_AnimationBlock AnimationBlock_AmbientColor;		// Float32x3
			CElement_AnimationBlock AnimationBlock_AmbientIntensity;	// Float32
			CElement_AnimationBlock AnimationBlock_DiffuseColor;		// Float32x3
			CElement_AnimationBlock AnimationBlock_DiffuseIntensity;	// Float32
			CElement_AnimationBlock AnimationBlock_AttenuationStart;	// Float32
			CElement_AnimationBlock AnimationBlock_AttenuationEnd;		// Float32
			CElement_AnimationBlock AnimationBlock_Visibility;			// UInt16
		};

		ASSERT_SIZE(CElement_Light, 156);

		//
		//
		class CElement_Camera
		{
		public:
			enum ECameraType : SInt32
			{
				FlyBy = -1,
				Portrait = 0,
				PaperDoll = 1
			};

			ECameraType Type;
			Float32 ClipFar;
			Float32 ClipNear;
			CElement_AnimationBlock AnimationBlock_Position;		// Float32x3
			C3Vector Position;
			CElement_AnimationBlock AnimationBlock_Target;			// Float32x3
			C3Vector Target;
			CElement_AnimationBlock AnimationBlock_Roll;			// Float32
			CElement_AnimationBlock AnimationBlock_FieldOfView;		// Float32	// v4
		};

		ASSERT_SIZE(CElement_Camera, 116);

		class CElement_Camera_PreCata
		{
		public:
			enum ECameraType : SInt32
			{
				FlyBy = -1,
				Portrait = 0,
				PaperDoll = 1
			};

			ECameraType Type;
			Float32 FoV;
			Float32 ClipFar;
			Float32 ClipNear;
			CElement_AnimationBlock AnimationBlock_Position;		// Float32x3
			C3Vector Position;
			CElement_AnimationBlock AnimationBlock_Target;			// Float32x3
			C3Vector Target;
			CElement_AnimationBlock AnimationBlock_Roll;			// Float32
		};

		ASSERT_SIZE(CElement_Camera_PreCata, 100);

		//
		//
		class CElement_CameraLookup
		{
		public:
			UInt16 Index;
		};

		ASSERT_SIZE(CElement_CameraLookup, 2);

		//
		//
		class CElement_RibbonEmitter
		{
		public:
			SInt32 ID;
			SInt32 ParentBone;
			C3Vector Position;
			M2Array Texture;
			M2Array RenderFlag;
			CElement_AnimationBlock AnimationBlock_Color;		// Float32x3
			CElement_AnimationBlock AnimationBlock_Opacity;		// UInt16
			CElement_AnimationBlock AnimationBlock_HeightAbove;	// Float32, position of point A of ribbon leading edge.
			CElement_AnimationBlock AnimationBlock_HeightBelow;	// Float32, position of point B of ribbon leading edge.
			Float32 EdgesPerSecond;
			Float32 EdgeLifetime;
			Float32 EmissionAngle;		// use arcsin(val) to get the angle in degree.
			UInt16 TextureRows;
			UInt16 TextureCols;
			CElement_AnimationBlock AnimationBlock_TexSlotTrack;	// SInt32
			CElement_AnimationBlock AnimationBlock_Visibility;	// SInt16
			SInt16 PriorityPlane;
			UInt16 Padding;
		};

		ASSERT_SIZE(CElement_RibbonEmitter, 176);

		//
		// 492 0x1EC
		class CElement_ParticleEmitter
		{
		public:
			UInt32 ID;				// always -1?
			UInt32 Flags;
			C3Vector Position;		// position relative to parent bone.
			UInt16 ParentBone;
			UInt16 Texture;
			M2Array FileNameModel;	// name of model to spawn *.mdx.
			M2Array ChildEmitter;

			UInt8 BlendingType;
			UInt8 EmitterType;
			UInt16 ParticleColorIndex;

			fixed_point<uint8_t, 2, 5> multiTextureParamX[2];

			UInt16 TextureTileRotation;
			UInt16 TextureDimensionsRows;
			UInt16 TextureDimensionsColumns;

			CElement_AnimationBlock AnimationBlock_EmitSpeed;		// Float32
			CElement_AnimationBlock AnimationBlock_SpeedVariance;	// Float32
			CElement_AnimationBlock AnimationBlock_VerticalRange;	// Float32
			CElement_AnimationBlock AnimationBlock_HorizontalRange;	// Float32
			CElement_AnimationBlock AnimationBlock_Gravity;			// Float32
			CElement_AnimationBlock AnimationBlock_Lifespan;		// Float32
			Float32 LifespanVary;
			CElement_AnimationBlock AnimationBlock_EmissionRate;	// Float32
			Float32 EmissionRateVary;
			CElement_AnimationBlock AnimationBlock_EmissionAreaLength;	// Float32
			CElement_AnimationBlock AnimationBlock_EmissionAreaWidth;	// Float32
			CElement_AnimationBlock AnimationBlock_zSource;			// Float32

			CElement_FakeAnimationBlock ColorTrack;
			CElement_FakeAnimationBlock AlphaTrack;
			CElement_FakeAnimationBlock ScaleTrack;
			C2Vector ScaleVary;
			CElement_FakeAnimationBlock HeadCellTrack;
			CElement_FakeAnimationBlock TailCellTrack;
			Float32 TailLength;
			Float32 TwinkleSpeed;
			Float32 TwinklePercent;
			CRange TwinkleScale;
			Float32 BurstMultiplier;
			Float32 Drag;
			Float32 BaseSpin;
			Float32 BaseSpinVary;
			Float32 Spin;
			Float32 SpinVary;

			M2Box Tumble;

			C3Vector WindVector;
			Float32 WindTime;
			
			Float32 FollowSpeed1;
			Float32 FollowScale1;
			Float32 FollowSpeed2;
			Float32 FollowScale2;

			M2Array SplinePoints;	// C3Vector
			CElement_AnimationBlock AnimationBlock_EnabledIn;		// UInt16

			vector_2fp_6_9 multiTextureParam0[2];
			vector_2fp_6_9 multiTextureParam1[2];
		};

		ASSERT_SIZE(CElement_ParticleEmitter, 492);

#pragma pack(pop)
	}
}

