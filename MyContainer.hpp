#pragma once
/**
 * TODO:
 * 1. add - gettimg an object and insert it to the container 		V
 * 2. remove - getting an object and removes from the container 	V
 * 		if the object does not exist - THROW 						V
 * 		if the object occurs 2+, remove all the entities			V
 * 3. size - retunrs the size of the container (not capacity) 		V
 * 4. operator<< - for prints 										V
 * 
 * ITERATORS:
 * 1. AscendingOrder												X
 * 2. DescendingOrder												X
 * 3. SideCrossOrder												X
 * 4. ReverseOrder
 * 5. Order
 * 6. MiddleOutOrder
 *  METHODS:
 * 1. begin()
 * 2. end()
 * 3. operator<
 * 4. operator>
 * 5. operator==
 * 6. operator<=
 * 7. operator>=
 * 8. operator--
 * 9. operator++
 * 10. all other operators that are relevant for containers
 */
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

namespace ariel{
	
	template <typename T> class MyContainer{
		private:
			vector<T> data;
		public:
			// ctr
			MyContainer();
			// cctr
			MyContainer(const MyContainer& o);
			// dtr
			~MyContainer();

			/**
			 * @brief Assign operator, part of rule of 3
			 * 
			 * @param o The container
			 * @return MyContainer& 
			 */
			MyContainer& operator=(const MyContainer& o){
				if (this != & &o){
					swap(this->data, o.data);
				}
				else *this;
			}

			/**
			 * @brief Adding an object to the container
			 * 
			 * @param o The object that we want to add
			 */
			void add(T o){
				data.push_back(o);
			}

			/**
			 * @brief getting an object and removes from the container
			 * if the object does not exist - THROW
			 * if the object occurs 2+, remove all the entities
			 * 
			 * @param o 
			 */
			void remove(T o){
				bool found_flag = false;
				for (size_t i = 0; i < this->size(); i++)
				{
					if(data.at(i) == o){
						found_flag = true;
						data.erase(data.begin()+i);
						i--;
					}
				}
				if(!found_flag){
					throw std::invalid_argument("ERROR: The requested object does not exist!\n");
				}
				
			}

			/**
			 * @brief Returns the size of the contaisn (not capacity)
			 * 
			 * @return int 
			 */
			int size(){
				return data.size();
			}

			/**
			 * @brief Helper operator to print the container
			 * 
			 * @tparam U 
			 * @param os 
			 * @param container The container
			 * @return ostream& 
			 */
			template <typename U>
			friend ostream& operator<<(ostream& os, const MyContainer<U>& container){
				os<< "{";
				size_t index = 0;
				for (index; index < container.size()-1; index++)
				{
					os<< container.data.at(index);
					os<< ", ";
				}
				os<< container.data.at(index+1);

				os<<"}" << endl;
			}	
	};
}