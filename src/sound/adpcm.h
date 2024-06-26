#ifndef ADPCM_H
#define ADPCM_H
#if !defined(__GNUC__) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || (__GNUC__ >= 4) // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#define MAX_ADPCM		16
#define MAX_OKIM6295	(MAX_ADPCM/4)	// 4 voices per chip


/* a generic ADPCM interface, for unknown chips */

struct ADPCMinterface
{
	int num;			       /* total number of ADPCM decoders in the machine */
	int frequency;             /* playback frequency */
	int region;                /* memory region where the samples come from */
	int mixing_level[MAX_ADPCM];     /* master volume */
};

int ADPCM_sh_start(const struct MachineSound *msound);
void ADPCM_sh_stop(void);
void ADPCM_sh_update(void);

void ADPCM_play(int num, int offset, int length);
void ADPCM_setvol(int num, int vol);
void ADPCM_stop(int num);
int ADPCM_playing(int num);


/* an interface for the OKIM6295 and similar chips */

/*
  Note about the playback frequency: the external clock is internally divided,
  depending on pin 7, by 132 (high) or 165 (low). This isn't handled by the
  emulation, so you have to provide the didvided internal clock instead of the
  external clock.
*/
struct OKIM6295interface
{
	int num;                  		/* total number of chips */
	double frequency[MAX_OKIM6295];	/* playback frequency */
	int region[MAX_OKIM6295];		/* memory region where the sample ROM lives */
	int mixing_level[MAX_OKIM6295];	/* master volume */
};

int OKIM6295_sh_start(const struct MachineSound *msound);
void OKIM6295_sh_stop(void);
void OKIM6295_sh_update(void);
void OKIM6295_set_bank_base(int which, int base);
void OKIM6295_set_pin7(int which, double aclock, unsigned char pin7);

READ_HANDLER( OKIM6295_status_0_r );
READ_HANDLER( OKIM6295_status_1_r );
READ_HANDLER( OKIM6295_status_2_r );
READ16_HANDLER( OKIM6295_status_0_lsb_r );
READ16_HANDLER( OKIM6295_status_1_lsb_r );
READ16_HANDLER( OKIM6295_status_2_lsb_r );
READ16_HANDLER( OKIM6295_status_0_msb_r );
READ16_HANDLER( OKIM6295_status_1_msb_r );
READ16_HANDLER( OKIM6295_status_2_msb_r );
WRITE_HANDLER( OKIM6295_data_0_w );
WRITE_HANDLER( OKIM6295_data_1_w );
WRITE_HANDLER( OKIM6295_data_2_w );
WRITE16_HANDLER( OKIM6295_data_0_lsb_w );
WRITE16_HANDLER( OKIM6295_data_1_lsb_w );
WRITE16_HANDLER( OKIM6295_data_2_lsb_w );
WRITE16_HANDLER( OKIM6295_data_0_msb_w );
WRITE16_HANDLER( OKIM6295_data_1_msb_w );
WRITE16_HANDLER( OKIM6295_data_2_msb_w );
#ifdef PINMAME
WRITE_HANDLER( OKIM6376_data_0_w );
#endif
#endif
