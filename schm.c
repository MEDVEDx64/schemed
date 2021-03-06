/*
 *  ===============================================
 *
 *	schm.c
 *
 *	Worms Armageddon game
 *	scheme file format library
 *
 *	This file IS NOT a part of original
 *	Worms Armageddon source code, this is
 *	an attempt to represent the scheme system
 *	of W:A. This library can be redistributed
 *	under the terms of GNU General Public License.
 *
 *	(C) MEDVEDx64, 2012.
 *	- Last updated: 2012.08.28 -
 *
 *  ===============================================
 */

#include "schm.h"

/** Creates an empty scheme structure **/
SCHM_FILE schm_blank ()
{
	void *buf = malloc(SCHM_LENGTH);
	int x;
	for(x = 0; x < SCHM_LENGTH; x++)
		*((unsigned char*)(buf+x)) = 0;

	SCHM_FILE scheme = *(SCHM_FILE*)buf;

	scheme.signature = SCHM_SIGNATURE;
	scheme.version = SCHM_FILE_VERSION;
	return scheme;
}

/** Loads a scheme file **/
SCHM_FILE schm_load ( const char* fname )
{
	FILE* schm_file;
	SCHM_FILE scheme = schm_blank ();

	/* Trying to open the file */
	if ( ( schm_file = fopen ( fname, "rb" ) ) == NULL )
	{
		/* Return 1 (in the signature field)
		if an attempt has failed */
		scheme.signature = 1;
		return scheme;
	}

	/* Getting the length of the file */
	long fsize;
	fseek ( schm_file , 0 , SEEK_END );
	fsize = ftell ( schm_file );
	rewind ( schm_file );

	/* Checking the file length and loading the scheme */
	int dummy = 0;
	if ( fsize == SCHM_LENGTH )
		dummy = fread(&scheme, 1, SCHM_LENGTH, schm_file);
	else if ( fsize == SCHM_LENGTH_OLD_FORMAT )
		dummy = fread(&scheme, 1, SCHM_LENGTH_OLD_FORMAT, schm_file);
	else
	{
		scheme.signature = 2;
		return scheme;
	}

	/* Finally we gonna check the signature */
	if ( scheme.signature != SCHM_SIGNATURE )
	{
		/* Return 3 if mismatch */
		scheme.signature = 3;
		return scheme;
	}

	fclose(schm_file);
	return scheme;
}

/** Writes a scheme to file **/
int schm_save ( const char* fname, SCHM_FILE scheme )
{
	FILE* schm_file;

	/* Opening the file... */
	if ( ( schm_file = fopen ( fname, "wb" ) ) == NULL )
		return 1;

	/* Checking the signature */
	if ( scheme.signature != SCHM_SIGNATURE )
	{
		/* ...and fixing it when mismatch */
		printf(" > schm_save() warning: fixing wrong scheme signature.\n");
		scheme.signature = SCHM_SIGNATURE;
	}

	/* Forcing the version field to "new version" */
	if(scheme.version != SCHM_FILE_VERSION)
	{
		printf(" > schm_save warning: fixing wrong scheme version field.\n");
		scheme.version = SCHM_FILE_VERSION;
	}

	/* Now let's write out it all */
	fwrite(&scheme, 1, SCHM_LENGTH, schm_file);
	fclose(schm_file);
	return 0;
}