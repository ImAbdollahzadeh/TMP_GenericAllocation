# TMP_GenericAllocation

in this application, we define a ListOfTypes using template metaprogramming. 
By default we allocated a container including dynamically allocated memory for each of those types.
For instance, we define a list ListOfTypes< int, char, double, int>. Now we have a container in which the first 4 elements are:

Container[0] = int Pointer to a dynamically allocated container for int.
              -----
              
Container[1] = char Pointer to a dynamically allocated container for char.
              ------    
              
Container[2] = double Pointer to a dynamically allocated container for double.
              --------
              
Container[3] = int Pointer to a dynamically allocated container for int.
              -----

