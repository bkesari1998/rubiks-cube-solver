#include <stdio.h>
#include <stdlib.h>
#include "vectors.h"

struct vector {
	int size;
	int capacity;
	char* data;
};
typedef struct vector Vector;

/**
 * Initializes a vector object
 *
 * @return
 * Returns a handle to a vector object
 */
VECTOR vector_init(void)
{
	// Allocate memory for a Vector object
	Vector* pVector = (Vector*)malloc(sizeof(VECTOR));
	
	// Execute if pVector allocation successful
	if (pVector != NULL)
	{
		// Initialize size and capacity
		pVector->size = 0;
		pVector->capacity = 10;
		
		// Allocate memory for data array
		pVector->data = (char*)malloc(sizeof(char) * (pVector->capacity));
		
		// Return NULL pointer if data memory allocation unsuccessful
		if (pVector->data == NULL)
		{
			return NULL;

		}

		// Return VECTOR pointer if object creation successful
		return (VECTOR)pVector;
	}
	
	// Return NULL if object creation unsuccessful
	return NULL;
}

/**
 * Frees heap memory associated with a vector object
 *
 * @param phVector
 * A pointer to the handle of the vector to be destroyed
 */
void vector_destroy(VECTOR* phVector)
{
	Vector* pVector = (Vector*) *phVector;
	
	// Execute if pVector != NULL
	if (pVector != NULL)
	{
		// Execute if data != NULL
		if (pVector->data != NULL)
		{
			// Free data
			free(pVector->data);
		}
		
		// Free pVector
		free(pVector);

		// Set phVector to NULL
		phVector = NULL;
		
		return;
	}
	
	return;
}

/**
 * Inserts an item at the back of the data array of a Vector object
 *
 * @param hVector
 * Handle to a Vector object
 *
 * @param item
 * The character to be appended to the data array of the Vector object
 */
void vector_append_item(VECTOR hVector, char item)
{
	Vector* pVector = (Vector*)hVector;
	
	// Execute if pVector != NULL
	if (pVector != NULL)
	{
		// Execute if data != NULL
		if (pVector->data != NULL)
		{
			// Check that data has enough space
			if (pVector->size >= pVector->capacity)
			{
				pVector->capacity *= 2;
				pVector->data = (char*)realloc(pVector->data, sizeof(char) * pVector->capacity);
			}
			
			// Append the number to the array
			pVector->data[pVector->size] = item;
			pVector->size += 1;
			return;
		}

	}
    
	// Output error message if append failed
	fprintf(stderr, "Could not append num.\n");
	return;
}

/**
 * Replaces an item in the data array of a Vector object
 *
 * @param hVector
 * Handle to a Vector object
 *
 * @param index
 * The index in the data aray of the item to be replaced
 *
 * @param item
 * The item that will be inserted into the data array
 */
void vector_replace_item(VECTOR hVector, unsigned int index,  char item)
{

	 Vector* pVector = (Vector*)hVector;

    // Execute if pVector != NULL
    if (pVector != NULL)
    {
        // Execute if data != NULL
        if (pVector->data != NULL)
        {
            // Check index is valid
            if (pVector->size > index)
            {
                pVector->data[index] = item;
                return;
            }
        }
    }

    // Output error message if replace failed
    fprintf(stderr, "Could not replace num.\n");
    return;
}

/**
 * Inserts an item into the data array of a Vector object at a specified index
 *
 * @param hVector
 * Handle to a Vector object
 *
 * @param index
 * The index at which the item will be inserted
 *
 * @param item
 * The item that wll be inserted into the data array
 */
void vector_insert_item(VECTOR hVector, unsigned int index, char item)
{
 	Vector* pVector = (Vector*)hVector;

    // Execute if pVector != NULL
    if (pVector != NULL)
    {
        // Execute if data != NULL
        if (pVector->data != NULL)
        {
            // Check that data has enough space
            if (pVector->size >= pVector->capacity)
            {
                pVector->capacity *= 2;
                pVector->data = (char*)realloc(pVector->data, sizeof(char) * pVector->capacity);
            }
        }

        // Check that index is valid
        if (pVector->size > index)
        {
            // Insert num into array and shift other elements right
            for (int i = pVector-> size - 1; i >= index; --i)
            {
                pVector->data[i + 1] = pVector->data[i];
            }
            
            pVector->data[index] = item;
            pVector->size += 1;
            return;
        }
    }

    // Output error message if append failed
    fprintf(stderr, "Could not append num.\n");
    return;
}

/**
 * Gets the size of a Vector object
 *
 * @param hVector
 * Handle to a Vector object
 *
 * @return
 * Returns the size of a Vector object
 */
int vector_get_size(VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	
	if (pVector != NULL)
	{
		return pVector->size;
	}

    // Output error message and return error number if operation failed
    fprintf(stderr, "Could not get vector size.\n");
	return -123456789;
}

/**
 * Gets the capacity of a Vector object
 *
 * @param hVector
 * Handle to a Vector object
 *
 * @return
 * Returns the capacity of a Vector object
*/
int vector_get_capacity(VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	
	if (pVector != NULL)
	{
		return pVector->capacity;
	}
	
    // Output error message and return error number if operation failed
    fprintf(stderr, "Could not get vector capacity.\n");
	return -123456789;
}

/**
 * Gets the character located at a specified index in the data array of a Vector object
 *
 * @param hVector
 * Handle to a Vector object
 *
 * @param index
 * The index of the character to return in the data array
 *
 * @return
 * Returns the character in the data array at the specified index
 */
char vector_pop_item (VECTOR hVector, unsigned int index)
{
	Vector* pVector = (Vector*)hVector;

	// Execute if pVector != NULL
	if (pVector != NULL)
	{
		// Execute if data != NULL
		if (pVector->data != NULL)
		{
			// Execute if index is valid
			if (pVector->size > index)
			{
				return pVector->data[index];
			}
		}
	}
	
	// Print error message and return NULL char if not able to get character
	fprintf(stderr, "Could not get value at index.\n");
    return '\0';
}

/**
 * Removes an item from the data array of a Vector object located at a specified index
 *
 * @param hVector
 * Handle to a Vector object
 *
 * @param index
 * The index of the item to be removed from the data array
 */
void vector_remove_item(VECTOR hVector, unsigned int index)
{
 	Vector* pVector = (Vector*)hVector;
        
    // Execute if pVector != NULL
    if (pVector != NULL)
    {
        // Execute if data != NULL
        if (pVector->data != NULL)
        {
            // Check that index is in bounds
            if (pVector->size > index)
            {
                // remove num into array and shift other elements left
                for (int i = index; i < pVector->size - 1; ++i)
                {
                    pVector->data[i] = pVector->data[i + 1];
                }
                
				// Reduce size by 1
                pVector->size -= 1;
                return;
            }
        }
    }
    
    // Output error message if remove failed
    fprintf(stderr, "Could not remove item at index.\n");
    return;
}

/**
 * Prints the characters in the data array of a Vector object to a file
 *
 * @param hVector
 * Handle to a Vector object
 *
 * @param fp
 * Pointer to the file to write to
 */
void vector_print_data(VECTOR hVector, FILE* fp)
{
	Vector* pVector = (Vector*)hVector;

	// Execute if pVector != NULL
	if (pVector != NULL)
	{
		// Execute if data != NULL
		if (pVector->data != NULL)
		{
			for (int i = 0; i < pVector->size; ++i)
			{
                fprintf(fp, "%c ", pVector->data[i]);
			}
			return;
		}
	}
	
	// Print error message if data was not printable
	fprintf(stderr, "Could not print vector data\n");
	return;
}

