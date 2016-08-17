#include <FastLED.h>
#include "ledarray.h"

//todo: pull these out of the main ino
#define NUM_STRIPS 8
#define NUM_LEDS_PER_STRIP 5
#define NUM_LEDS 40

LEDArray::LEDArray(struct CRGB *_leds, long _NUM_LEDS){
	leds=_leds;
	num_leds=_NUM_LEDS;
}

//================================================================================
// init routines

void LEDArray::init_off(){
	fill_solid(leds,num_leds,CHSV(0,0,0));
}


void LEDArray::init_noise(){
	for(int i=0; i<num_leds; i++){
			leds[i] = CHSV(random(255),255,255);
		}
}

void LEDArray::init_rainbow(){
	fill_gradient(leds,num_leds,CHSV(0,255,255),CHSV(1,255,255),LONGEST_HUES);
}

void LEDArray::init_ringbow(){
	for(int i=0; i<num_leds; i++){
			leds[i] = CHSV((i%NUM_LEDS_PER_STRIP)*255.0/NUM_STRIPS,255,255);
		}
}


void LEDArray::init_single(){
	fill_solid(leds,num_leds,CHSV(0,0,0));
	leds[1]=CRGB(255,255,255);
}

void LEDArray::init_inner(){
	fill_solid(leds,num_leds,CHSV(0,0,0));
	for(int i=0; i<num_leds-1; i+=5){
		leds[i]=CHSV(i*5,255,128);
	}

	
}

void LEDArray::init_spiral(){
	fill_solid(leds,num_leds,CHSV(0,0,0));
	for(int i=0; i<num_leds-1; i+=6){
		leds[i]=CHSV(i*5,255,128);
	}

	
}

void LEDArray::init_line(){
	fill_solid(leds,num_leds,CHSV(0,0,0));
	fill_solid(leds,5,CHSV(10,255,128));	
}


void LEDArray::init_checkerboard(){
	fill_solid(leds,num_leds,CHSV(0,0,0));
	for(int i=0; i<num_leds-1; i+=2){
		leds[i]=CHSV(i*5,255,128);
	}

	
}

//================================================================================
// animation routines

void LEDArray::rotate_rank(int rank){
	
	int i=rank;
	CRGB led0=leds[i];
	for(; i<(NUM_LEDS-NUM_LEDS_PER_STRIP); i+=NUM_LEDS_PER_STRIP){
			leds[i] = leds[i+NUM_LEDS_PER_STRIP];
		}
		
	leds[i]=led0;
}

void LEDArray::rotate_rank_reverse(int rank){
	
	int i=NUM_LEDS-NUM_LEDS_PER_STRIP+rank;
	CRGB ledn=leds[i];
	for(; i>NUM_LEDS_PER_STRIP-1; i-=NUM_LEDS_PER_STRIP){
			leds[i] = leds[i-NUM_LEDS_PER_STRIP];
		}
		
	leds[i]=ledn;
}

void LEDArray::spin_cw(){
	for(int i=0; i<NUM_LEDS_PER_STRIP; i++){
		rotate_rank(i);
	}
} 

void LEDArray::spin_ccw(){
	for(int i=0; i<NUM_LEDS_PER_STRIP; i++){
		rotate_rank_reverse(i);
	}
} 

void LEDArray::spinterlace(){
	for(int i=0; i<NUM_LEDS_PER_STRIP; i++){
		if(i%2==0){
			rotate_rank_reverse(i);
		} else {
			rotate_rank(i);
		}
	}
} 

void LEDArray::rotate_file(int file){
	
	int i=file*NUM_LEDS_PER_STRIP;
	CRGB led0=leds[i];
	for(; i<((file+1)*NUM_LEDS_PER_STRIP)-1; i++){
			leds[i] = leds[i+1];
		}
		
	leds[i]=led0;
}


void LEDArray::rotate_file_reverse(int file){
	
	int i=(file+1)*NUM_LEDS_PER_STRIP-1;
	CRGB ledn=leds[i];
	for(; i>(file*NUM_LEDS_PER_STRIP); i--){
			leds[i] = leds[i-1];
		}
		
	leds[i]=ledn;
}


void LEDArray::implode(){
	for(int i=0; i<NUM_STRIPS; i++){
		rotate_file(i);
	}
} 

void LEDArray::explode(){
	for(int i=0; i<NUM_STRIPS; i++){
		rotate_file_reverse(i);
	}
} 

/*
void LEDArray::rotate(){
	CRGB led0=leds[0];
	for(int i=0; i<num_leds-1; i++){
			leds[i] = leds[i+1];
		}
		
	leds[num_leds-1]=led0;
}
*/

void LEDArray::rotate_hue(){
	for(int i=0; i<num_leds; i++){
			CHSV hsv=rgb2hsv_approximate(leds[i]);
			hsv.hue=(( (int) hsv.hue)+2) % 256;
			//hsv.hue=3;
			leds[i] = hsv;
		}
		
	
}

uint8_t blend_hues(uint8_t one, uint8_t two){
	long diff=one-two;
	long avg;
	if(abs(diff)<128){
		avg=0.5*one+0.5*two;
	} else {
		avg=((long) (0.5*one+0.5*two+128)) % 256;
	}
	
	return (uint8_t) avg-1;
}

void LEDArray::blur(){
	CHSV prev=CHSV(random(255),255,255);
	CHSV current=rgb2hsv_approximate(leds[0]);
	CHSV next;
	int i;
	for(i=0; i<num_leds-1; i++){
		CHSV next=rgb2hsv_approximate(leds[i+1]);
		leds[i]=CHSV(blend_hues(current.hue,blend_hues(prev.hue,next.hue)),255,255);
		prev=current;
		current=next;
	}
	
	next=CHSV(random(255),255,255);
	leds[i]=CHSV(blend_hues(current.hue,blend_hues(prev.hue,next.hue)),255,255);
}


void LEDArray::rand_swap(){
	long pos=random(num_leds);
	long pos2=random(num_leds);
	CRGB tmp = leds[pos];
	leds[pos] = leds[pos2];
	leds[pos2] = tmp;
}

void LEDArray::rand_swapn(){
	for(int i=0; i<100; i++){
		rand_swap();
	}
}


void LEDArray::rand_hue(){
	long pos=random(num_leds);
	leds[pos] = CHSV(random(255),255,255);
}

void LEDArray::rand_huen(){
	for(int i=0; i<100; i++){
		rand_hue();
	}
}

void LEDArray::generate_starfield(){
	int num_stars=random(5);
	for(int i=0; i<NUM_STRIPS; i++){
		leds[NUM_LEDS_PER_STRIP*i]=CHSV(0,0,0);
	}
	
	for(int i=0; i<num_stars; i++){
			leds[NUM_LEDS_PER_STRIP*random(NUM_STRIPS)] = CHSV(random(255),random(50),random(255));
		}
}


void LEDArray::gears(){
	static int step=0;
	static int step1=0;
	static int step2=0;
	static int step3=0;
	step=(step+1)%NUM_STRIPS;
	rotate_rank(0);
	if(step==0){
		rotate_rank(1);
		step1=(step1+1)%NUM_STRIPS;
		
		if(step1==0){
			rotate_rank(2);
			step2=(step2+1)%NUM_STRIPS;
			
			if(step2==0){
				rotate_rank(3);
				step3=(step3+1)%NUM_STRIPS;
				
				if(step3==0){
					rotate_rank(4);
				}
			}
		}
	}
} 


void LEDArray::galaxy(){
	static int step=0;
	step=(step+1)%8;
	if(step==0){
		explode();
		generate_starfield();
	}
		spin_cw();
} 
