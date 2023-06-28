#include "level.h"

#include <iostream>



#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>



int Object::GetPropertyInt(std::string name)
{
    return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(std::string name)
{
    return strtod(properties[name].c_str(), NULL);
}

std::string Object::GetPropertyString(std::string name)
{
    return properties[name];
}
Level::Level(SDL_Renderer* ren) {
    renderer = ren;
}
Level:: ~Level() {
    delete renderer;
}

bool Level::LoadFromFile(std::string filename)
{

    tmx::Map map;


	// ��������� XML-�����
    if(!map.load(filename))
    {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }


	// ������ �����: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
    tmx::FloatRect bounds = map.getBounds();
    tileWidth = map.getTileSize().x;
    tileHeight = map.getTileSize().y;

    width = map.getBounds().width / tileWidth;
    height = map.getBounds().height / tileHeight;
    

	// ����� �������� �������� � ������������� ������� �����
    const auto& tilesetElement = map.getTilesets()[0];
    firstTileID = tilesetElement.getFirstGID();

	// source - ���� �� �������� � ���������� image
    std::string imagepath = tilesetElement.getImagePath();

	// �������� ��������� �������
	SDL_Surface* img = IMG_Load(imagepath.c_str());

    if(img == nullptr)
    {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }

	// ������� ����� �� ����� (109, 159, 185)
	// ������-�� � �������� ����� ���� ��� ������ �����, �� � �� ����� �������, ��� 16-������ ������
	// ����� "6d9fb9" ������������� � ����
    //img.createMaskFromColor(sf::Color(109, 159, 185));
	// ������ �������� �� �����������
	tilesetImage = SDL_CreateTextureFromSurface(renderer, img);


	// �������� ���������� �������� � ����� ��������
    SDL_Point size;
    SDL_QueryTexture(tilesetImage, NULL, NULL, &size.x, &size.y);
    int columns = size.x / tileWidth;
    int rows = size.y / tileHeight;
    
	// ������ �� ��������������� ����������� (TextureRect)
  /**/  std::vector<SDL_Rect> subRects;

	for (int y = 0; y < rows; y++)
	    for(int x = 0; x < columns; x++)
	    {
		    SDL_Rect rect;
		    rect.y = y * tileHeight;
		    rect.h = tileHeight;
		    rect.x = x * tileWidth;
		    rect.w = tileWidth;

		    subRects.push_back(rect);
	    }
    /**/
	// ������ �� ������
    const auto& buffLayers = map.getLayers();
    
    for(const auto &layerElement: buffLayers)
    {
        Layer layer;
		
        const auto &tileSets = map.getTilesets();
        const auto &layerIDs = layerElement.get()->getLayerAs<tmx::TileLayer>().getTiles();
      
        /**/
     
        /**/
        int x = 0;
        int y = 0;
        
        for (const auto &tileElement :layerIDs)
        {
            int tileGID =  tileElement.ID;
            int subRectToUse = tileGID - firstTileID;
            
			// ������������� TextureRect ������� �����
            if (subRectToUse >= 0)
            {
                Sprite* sprite = new Sprite();
                sprite->setTexture(tilesetImage);
                sprite->setTextureRect(subRects[subRectToUse]);
                sprite->setPosition(x * tileWidth, y * tileHeight);
                sprite->setScale(1,1);
                SDL_Rect textureRect = subRects[subRectToUse];


                layer.tiles.push_back(sprite);
            }

           

            x++;
            if (x >= width)
            {
                x = 0;
                y++;
                if(y >= height)
                    y = 0;
            }
        }

        layers.push_back(layer);

        
    }
    /**/
    // ������ � ���������
   /* TiXmlElement* objectGroupElement;

	// ���� ���� ���� ��������
    if (map.FirstChildElement("objectgroup") != NULL)
    {
        objectGroupElement = map.FirstChildElement("objectgroup");
        while (objectGroupElement)
        {
			// ��������� <object>
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");
           
			while(objectElement)
            {
				// �������� ��� ������ - ���, ���, �������, etc
                std::string objectType;
                if (objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != NULL)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

				int width, height;

				Sprite* sprite = new Sprite();
                sprite->setTexture(tilesetImage);
                sprite->setTextureRect(SDL_Rect{ 0,0,0,0 });
                sprite->setPosition(x, y);
                sprite->setScale(1,1);

				if (objectElement->Attribute("width") != NULL)
				{
					width = atoi(objectElement->Attribute("width"));
					height = atoi(objectElement->Attribute("height"));
				}
				else
				{
					width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].w;
					height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].h;
				    sprite->setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
				}

				// ��������� �������
                Object object;
                object.name = objectName;
                object.type = objectType;
				object.sprite = sprite;

                SDL_Rect objectRect;
                objectRect.y = y;
                objectRect.x = x;
				objectRect.h = height;
				objectRect.w = width;
                object.rect = objectRect;

				// "����������" �������
                TiXmlElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL)
                {
                    TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL)
                    {
                        while(prop)
                        {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

				// ������ ������ � ������
                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }/**/

    return true;
}

Object Level::GetObject(std::string name)
{
	// ������ ������ ������ � �������� ������
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].name == name)
            return objects[i];
}

std::vector<Object> Level::GetObjects(std::string name)
{
	// ��� ������� � �������� ������
	std::vector<Object> vec;
    for(int i = 0; i < objects.size(); i++)
        if(objects[i].name == name)
			vec.push_back(objects[i]);

	return vec;
}

Vector2D Level::GetTileSize()
{
	return Vector2D(tileWidth, tileHeight);
}

void Level::draw(SDL_Renderer *ren, SDL_Rect camera)
{
	// ������ ��� ����� (������� �� ������!)
    for (int layer = 0; layer < layers.size(); layer++)
        for (int tile = 0; tile < layers[layer].tiles.size(); tile++) {
            layers[layer].tiles[tile]->draw(ren, camera);
        }
}

/**/