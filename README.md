# Basic-naive-bayes-classification
Reads training text images which has digits in the form of patterns of '#' and ' '. Then classifies testing text images based on naive bayes classification
Also involves Laplace smoothing which was manually found to be equal to 0.1

Every image is in the form of 28*28 grids, ' ' represent a white pixel, # represents a black pixel and + represents a grey foreground pixel
program.cpp assumes a grey pixel and a black pixel and gives an accuracy of 77.3% over the testing data.
program2.cpp takes grey and black pixels as different and gives an accuracy of 77.5%.

Traininglabels has the resultant answers to the text images and similar is the pattern for testimages

Bayes Classification:
	P[ Class | F ] = (P[F | Class] P[Class]) / P[F]
	Since P[F] remains constant, maximizing this value means maximizing the numerator
	
	P[F | Class] = P[ f(1,1) | Class] * P[ f(1,2) | Class] * ......... * P[ f(28,28) | Class]
	Therefore the class that maximizes this probability will be our resultant class

Sample image:

                            
                            
                            
                            
                            
                            
                            
             ++###+         
             ######+        
            +######+        
            ##+++##+        
           +#+  +##+        
           +##++###+        
           +#######+        
           +#######+        
            +##+###         
              ++##+         
              +##+          
              ###+          
            +###+           
            +##+            
           +##+             
          +##+              
         +##+               
         ##+                
        +#+                 
        +#+                 
                            
							
Compilation: g++ program.cpp
Execute: ./a.out	OR		a.exe
