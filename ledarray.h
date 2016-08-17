#ifndef LEDARRAY_H
#define LEDARRAY_H

class LEDArray
{
	public:
		LEDArray(struct CRGB *_leds, long _NUM_LEDS);
		
	// initialization utilities	
		void init_off();
		void init_noise();
		void init_starfield();
		void init_rainbow();
		void init_ringbow();
		void init_single();
		void init_spiral();
		void init_inner();
		void init_line();
		void init_checkerboard();
		
	// animation utilities
		void rotate_hue();
		
		void rotate_rank(int rank);
		void rotate_rank_reverse(int rank);
		
		void spin_cw();
		void spin_ccw();
		void spinterlace();
		
		void rotate_file(int file);
		void rotate_file_reverse(int file);
		void implode();
		void explode();

		void blur();
		void rand_swap();
		void rand_swapn();
		void rand_hue();
		void rand_huen();
		
		void generate_starfield();
		
		void gears();
		void galaxy();
	//private:
		long num_leds;
		struct CRGB *leds;

};

#endif