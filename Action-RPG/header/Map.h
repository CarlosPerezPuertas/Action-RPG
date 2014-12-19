#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cassert>
#include <vector>
#include <string>



enum class TileType
{
	None,
	Walkable,
	Collidable,
	GhostCollidable,
	Especial
};

struct Layer
{
	sf::VertexArray entity_vertex;
	sf::Texture texture;
	int layer_id;
};

struct TMX_Tile
{
	TileType type;
	sf::FloatRect rect;
	sf::Vector2f center;
	int id;
	std::vector<int> adjacent_tiles;
};

struct TMX_Map
{
	sf::Vector2f tile_size;
	sf::Vector2u map_size;
	int num_layers;
	std::string sprite_sheet;
	std::vector<std::vector<int>> maps;
	std::vector<TMX_Tile> collision_map;
};


//#########Entity objects########

struct TMX_Door
{
	sf::FloatRect rect;
	std::string name;
	bool state;
	unsigned int texture_id;
	unsigned int frame_number;
	unsigned int frame_width;
	unsigned int frame_height;
};

struct TMX_Warp
{
	sf::FloatRect rect;
	std::string level_script;
	sf::Vector2f destiny;
	int orientation;
};




class Map : public sf::Drawable, public sf::Transformable
{
	public:
		Map();
		Map(const std::string &filename);
		~Map(){ std::cout << "Map deleted" << std::endl; }

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void draw_layer(sf::RenderTarget &target, int layer_id) const;
		void draw_layer(sf::RenderTarget &target, sf::RenderStates states, int layer_id) const;
		void update(sf::Time dt);

		//Read map from TMX file
		void load(const std::string &filename);
		void read_TMX(const std::string &filename);
		void load_collision_map();
		void load_layers(const std::string spritesheet, std::vector<std::vector<int>> &all_map, unsigned int width, unsigned int height, int layer_id);

		
		inline bool isActive() const { return active; }
		inline void enable(){ active = true; }
		inline void disable(){ active = false; }
		inline void disable(float seconds){ active = false; isTemporalDisabled = true; time_disabled = sf::seconds(seconds); }

		void scaleMap(sf::Vector2f &factor);
		void setMapPosition(sf::Vector2f pos);
		inline unsigned int getMapWidth(){ return tmx_info.map_size.x; }
		inline float getWidth() const { return tmx_info.map_size.x * tmx_info.tile_size.x * getScale().x; }
		inline float getHeight() const { return tmx_info.map_size.y * tmx_info.tile_size.y * getScale().y; }


	public:
		TMX_Map tmx_info;
		std::vector<TMX_Door> tmx_door;
		std::vector<TMX_Warp> tmx_warp;

	private:
		std::vector<Layer> map_layers;
		bool active;
		sf::Time time_disabled;
		bool isTemporalDisabled;
};




