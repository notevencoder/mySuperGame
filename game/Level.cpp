#include "level.h"

#include <iostream>



#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include "Game.h"




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
Level::Level(SDL_Renderer* ren, b2World* worldd) {
    
    world = worldd;
    renderer = ren;
    viewport = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

}
Level:: ~Level() {
    delete renderer;
}

bool Level::LoadFromFile(std::string filename)
{

    tmx::Map map;


	// Загружаем XML-карту
    if(!map.load(filename))
    {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }


	// Пример карты: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
    tmx::FloatRect bounds = map.getBounds();
    tileWidth = map.getTileSize().x;
    tileHeight = map.getTileSize().y;

    width = map.getBounds().width / tileWidth;
    height = map.getBounds().height / tileHeight;
    

	// Берем описание тайлсета и идентификатор первого тайла
    const auto& tilesetElement = map.getTilesets()[0];
    firstTileID = tilesetElement.getFirstGID();

	// source - путь до картинки в контейнере image
    std::string imagepath = tilesetElement.getImagePath();

	// Пытаемся загрузить тайлсет
	SDL_Surface* img = IMG_Load(imagepath.c_str());

    if(img == nullptr)
    {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }

	// Очищаем карту от света (109, 159, 185)
	// Вообще-то в тайлсете может быть фон любого цвета, но я не нашел решения, как 16-ричную строку
	// вроде "6d9fb9" преобразовать в цвет
    //img.createMaskFromColor(sf::Color(109, 159, 185));
	// Грузим текстуру из изображения
	tilesetImage = SDL_CreateTextureFromSurface(renderer, img);


	// Получаем количество столбцов и строк тайлсета
    SDL_Point size;
    SDL_QueryTexture(tilesetImage, NULL, NULL, &size.x, &size.y);
    int columns = size.x / tileWidth;
    int rows = size.y / tileHeight;
    
	// Вектор из прямоугольников изображений (TextureRect)
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
	// Работа со слоями
    const auto& buffLayers = map.getLayers();
    
    for(const auto &layerElement: buffLayers)
    {
        if (layerElement.get()->getType() == tmx::Layer::Type::Tile) {
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
            
			    // Устанавливаем TextureRect каждого тайла
                if (subRectToUse >= 0)
                {
                    Drawable sprite;
                    sprite.texture = tilesetImage;
                    sprite.srcrect = subRects[subRectToUse] ;
                    sprite.dstrect = SDL_FRect {(float) x * tileWidth,(float) y * tileHeight, 0, 0 };
                    
                    Transform box;
                    box.rect = sprite.dstrect;
                    

                    Entity entity = Coordinator::getInstance()->CreateEntity();
                    Coordinator::getInstance()->AddComponent(entity, sprite);
                    Coordinator::getInstance()->AddComponent(entity, box);
                   //push_back(sprite);
                    /**/
                        

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
        }else
            if (layerElement.get()->getType() == tmx::Layer::Type::Object) {
                auto const& objectGroup = layerElement.get()->getLayerAs<tmx::ObjectGroup>();
                for (const auto& obj : objectGroup.getObjects()) {
                   
                    std::string objectType = obj.getType();
                    std::string objectName = obj.getName();
                   

                    int x = obj.getPosition().x;
                    int y = obj.getPosition().y;

                    int width, height;
                    /*
                    Sprite* sprite = new Sprite();
                    sprite->setTexture(tilesetImage);
                    sprite->setTextureRect(SDL_Rect{ 0,0,0,0 });
                    sprite->setPosition(x, y);
                    sprite->setScale(1, 1);
                    /**/
                    if (obj.getAABB().width)
                    {
                        width = obj.getAABB().width;
                        height = obj.getAABB().height;
                    }
                    else
                    {
                        width = subRects[obj.getTileID() - firstTileID].w;
                        height = subRects[obj.getTileID() - firstTileID].h;
                        //sprite->setTextureRect(subRects[obj.getTileID() - firstTileID]);
                    }

                    // Экземпляр объекта
                    Object object;
                    object.name = objectName;
                    object.type = objectType;
                    //object.sprite = sprite;

                    SDL_FRect objectRect;
                    objectRect.y = y;
                    objectRect.x = x;
                    objectRect.h = height;
                    objectRect.w = width;
                    object.rect = objectRect;

                    


                    // "Переменные" объекта
                    const auto& properties = obj.getProperties();
                    if (!properties.empty())
                    {
                        for (const auto& prop : properties)

                        {

                            std::string propertyName = prop.getName();
                            std::string propertyValue = prop.getStringValue();

                            object.properties[propertyName] = propertyValue;

                        }
                    }
                    
                    b2BodyType btype = b2BodyType::b2_dynamicBody;

                    if (objectName == "Wall") {

                        btype = b2BodyType::b2_staticBody;
                    }
                    if (objectName == "Enemy") {
                        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, IMG_Load("Dungeon_Character.png"));
                        auto coor = Coordinator::getInstance();
                        Drawable sprite;
                        sprite.texture = tex;
                        sprite.srcrect = {32,32,16,16};
                        sprite.dstrect = object.rect;

                        Transform box;
                        box.rect = sprite.dstrect;

                        Entity  enemy = coor->CreateEntity();
                        coor->AddComponent(enemy, sprite);
                        coor->AddComponent(enemy, box);
                        

                       
                    }

                    if (layerElement.get()->getName() != "Player")
                     bodyFactory::getInstance().createRectBody(world, obj, btype);
                    
                    // Пихаем объект в вектор
                    objects.push_back(object);
                }


            }
        
    }
    /*
    // Работа с объектами
   /* */
   
	// Если есть слои объектов
   

    return true;
}

Object Level::GetObject(std::string name)
{
	// Только первый объект с заданным именем
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].name == name)
            return objects[i];
}

std::vector<Object> Level::GetObjects(std::string name)
{
	// Все объекты с заданным именем
	std::vector<Object> vec;
    for(int i = 0; i < objects.size(); i++)
        if(objects[i].name == name)
			vec.push_back(objects[i]);

	return vec;
}

b2Vec2 Level::GetTileSize()
{
	return b2Vec2(tileWidth, tileHeight);
}


void Level::draw(SDL_Renderer *ren, SDL_FRect camera)
{
    /*
	// Рисуем все тайлы (объекты НЕ рисуем!)
    for (int layer = 0; layer < layers.size(); layer++)
        for (int tile = 0; tile < layers[layer].tiles.size(); tile++) {
            layers[layer].tiles[tile]->draw(ren, camera);
        }
    /**/
}



/**/