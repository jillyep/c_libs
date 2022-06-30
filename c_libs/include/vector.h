// ================================================================================
// ================================================================================
// - File:    vector.h
// - Purpose: This file contains the prototype, structures, and enums used
//            in vector.c.
//
// Source Metadata
// - Author:  Jillian Epstein
// - Date:    June 29, 2022
// - Version: 1.0
// - Copyright: Copyright 2022, Jillian Epstein Inc.
// ================================================================================
// ================================================================================
// Include modules here

#ifndef vector_H
#define vector_H

#include <stdio.h>

/**
 *  An enum container with variables describing relevant data types
 *
 *  @param FLOAT An integer representing 4 bytes float data types
 *  @param DOUBLE An integer representing 8 byte double data types
 *  @param CHAR An integer representing 1 byte char data types
 *  @param INT An integer representing 4 bytes int data types
 *  @param STRING An integer representing a string data type as an array
 *				  of 1 byte characters
 *	@param SHORTINT An integer representing a 2 byte integer data type
 *	@param LONGINT An integer representing an 8 byte integer data type
 *	@param LONGLONG An integer representing a 16 byte integer or double data type
 *	@param NONE No data type assigned. This is used when the programmer
 *				wishes to create a vector of a unique data type. 
 */

typedef enum
{
	FLOAT,
	DOUBLE,
	CHAR,
	INT,
	STRING,
	SHORTINT,
	LONG,
	LONGLONG,
	NONE
}	dtype;

int func(); // Replace with correct prototype

#endif /* vector_H */
// ================================================================================
// ================================================================================
// eof
