#pragma once

#include "SceneNode.h"

class SoundNode : public SceneNode
{
	public:
		explicit SoundNode(int c_type, SoundBufferFactory &buffer_factory);
		explicit SoundNode(int c_type1, int c_type2, SoundBufferFactory &buffer_factory);
		virtual ~SoundNode();

		virtual unsigned int getCategory() const;
		void play();
		void playAfter(const float seconds);
		void playDuring(const float seconds);
		void updateCurrent(CommandQueue &command_queue, const sf::Time dt);
		void stop();
		void setLoop(bool x);
		void setPitch(float pitch);



	private:
		sf::Sound sound;	
		sf::Sound second_sound;
		sf::SoundBuffer buffer;
		int type;
		static bool first_waka;

		sf::Time time_after;

};

