#include <vector>
#include <cmath>


class MergeSort {
  
  public:
	
    template <class T>
    static std::vector<T> sort (std::vector<T> & v) 
    {
		if(v.size() > 1) {
			typename std::vector<T>::iterator mid = v.begin() + floor(v.size()/2);	//define mid
			
			std::vector<T> left = std::vector<T>(v.begin(), mid);	//create left half vector
			std::vector<T> right = std::vector<T>(mid, v.end());	//create right half vector
	
			left = sort(left);		//enter recursion
			right = sort(right);			
			
			return merge(v, left, right);	//merge and return
		}
		
		return v;	//base case, if v.size() is 1, then it's already sorted.
    }
    
    template <class T>
    static std::vector<T> merge(std::vector<T> & v, const std::vector<T> & left, const std::vector<T> & right)
    {    	
    	std::vector<T> toReturn;
    	unsigned int left_counter = 0;
    	unsigned int right_counter = 0;
    	
    	//compares left and right, pushing the smaller one (like two ladders)
    	while(left_counter < left.size() && right_counter < right.size())
    	{
    		T left_element = left.at(left_counter);
    		T right_element = right.at(right_counter);
    	
    		if(left_element < right_element)
    		{  			
    			toReturn.push_back(left_element);
    			left_counter++;
    		}
    		else
    		{  			
    			toReturn.push_back(right_element);
    			right_counter++;
    		}
    	}
    	
    	while(left_counter < left.size())	//pushes ALL remaining elements from left
    	{  		
    		toReturn.push_back(left.at(left_counter));
    		left_counter++;
    	}
    	
    	while(right_counter < right.size())	//pushes ALL remaining elements from right
    	{    		
    		toReturn.push_back(right.at(right_counter));
    		right_counter++;
    	}
    	v = toReturn;
    	
    	return v;
    }
};
