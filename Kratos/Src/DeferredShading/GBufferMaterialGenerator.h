/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2012 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
same license as the rest of the engine.
-----------------------------------------------------------------------------
*/


#ifndef _GBUFFER_MATERIAL_GENERATOR_H_
#define _GBUFFER_MATERIAL_GENERATOR_H_

#include "MaterialGenerator.h"

namespace Kratos
{
	/** Class for generating materials for objects to render themselves to the GBuffer
	*  @note This does not support all the possible rendering techniques out there.
	*  in order to support more, either expand this class or make sure that objects
	*  that will not get treated correctly will not have materials generated for them.
	*/
	class GBufferMaterialGenerator : public MaterialGenerator
	{
	public:

		//Constructor
		GBufferMaterialGenerator();

		//The relevant options for objects that are rendered to the GBuffer
		enum GBufferPermutations 
		{
			//(Regular) Textures
			GBP_NO_TEXTURES =			0x00000000,
			GBP_ONE_TEXTURE =			0x00000001,
			GBP_TWO_TEXTURES =			0x00000002,
			GBP_THREE_TEXTURES =		0x00000003,
			GBP_TEXTURE_MASK =			0x0000000F,

			//Material properties
			GBP_HAS_DIFFUSE_COLOUR =     0x00000010,

			//The number of texture coordinate sets
			GBP_NO_TEXCOORDS =			0x00000000,
			GBP_ONE_TEXCOORD =			0x00000100,
			GBP_TWO_TEXCOORDS =			0x00000200,
			GBP_TEXCOORD_MASK =			0x00000700,

			//法线贴图
			GBP_NORMAL_MAP =			0x00000800,

			//高光Color+SpecularPower纹理
			GBP_SPECULAR_MAP	=		0x00000020,

			//自发光图
			GBP_EMISSIVE_MAP	=		0x00000040,

			//贴花纹理
			GBP_DECAL_MAP		=		0x00000080,

			//Are we skinned?
			GBP_SKINNED			=		0x00010000,

			//Instancing
			GBP_INSTANCING_ONE_WEIGHT=	0x00100000,
			GBP_INSTANCING_TWO_WEIGHT=	0x00200000,
			GBP_INSTANCING_THREE_WEIGHT=0x00300000,
			GBP_INSTANCING_FOUR_WEIGHT=	0x00400000,
			GBP_INSTANCING_WEIGHT_MASK=	0x00700000,

			//队伍颜色
			GBP_TEAM_COLOR_RED	=		0x00001000,
			GBP_TEAM_COLOR_Blue	=		0x00002000,
			GBP_TEAM_COLOR_Mask	=		0x00003000,
		};

		//The mask of the flags that matter for generating the fragment shader
		static const Ogre::uint32 FS_MASK =		0x0000FFFF;

		//The mask of the flags that matter for generating the vertex shader
		static const Ogre::uint32 VS_MASK =		0x00FFFF00;

		//The mask of the flags that matter for generating the material
		static const Ogre::uint32 MAT_MASK =	0xFF00FFFF;
	};
}


#endif
