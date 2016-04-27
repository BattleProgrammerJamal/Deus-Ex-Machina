#ifndef TYPES_HPP
#define TYPES_HPP

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>

#define DEM_INT		std::int16_t
#define DEM_UINT	std::uint16_t
#define DEM_UCHAR	unsigned char

#define PTR_ALIGN_VALUE 16
#define AlignedPtr(ptr) (void*)(((uint32_t)ptr) + (PTR_ALIGN_VALUE - 1) & ~0xf)

namespace DEM
{
	namespace Types
	{
		enum SCENE_FILE_ITEM_TYPE
		{
			MESH = 1,
			MODEL_OBJ,
			DIRECTIONAL_LIGHT,
			POINT_LIGHT,
			CONVOLUTIONAL_MATERIAL,
			SOUND,
			MUSIC
		};

		static DEM_UINT parse(const std::string& type)
		{
			if (type == "Mesh"){ return MESH; }
			if (type == "ModelObj"){ return MODEL_OBJ; }
			if (type == "DirectionalLight"){ return DIRECTIONAL_LIGHT; }
			if (type == "PointLight"){ return POINT_LIGHT; }
			if (type == "ConvolutionalMaterial"){ return CONVOLUTIONAL_MATERIAL; }
			if (type == "Sound"){ return SOUND; }
			if (type == "Music"){ return MUSIC; }

			return 0;
		}
	};

	namespace StringUtility
	{
		static std::vector<std::string> Split(std::string chaine, char separateur)
		{
			std::vector<std::string> vecteur;

			std::string::size_type stTemp = chaine.find(separateur);

			while (stTemp != std::string::npos)
			{
				vecteur.push_back(chaine.substr(0, stTemp));
				chaine = chaine.substr(stTemp + 1);
				stTemp = chaine.find(separateur);
			}

			vecteur.push_back(chaine);
			return vecteur;
		}

		static std::string PaddingRemove(std::string str)
		{
			DEM_INT k = 0;
			for (DEM_UINT j = 0; j < str.size(); ++j)
			{
				if ((str[j] != ' ') || (str[j] == ' ' && str[j + 1] != ' '))
				{
					str[k] = str[j];
					++k;
				}
			}
			str.resize(k);

			if (str[k - 1] == ' ') { str.erase(str.end() - 1); }
			if (str[0] == ' ') { str.erase(str.begin()); }

			return str;
		}
	};
};

#endif