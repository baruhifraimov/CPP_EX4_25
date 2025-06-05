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
 * 4. ReverseOrder 													X
 * 5. Order 														X
 * 6. MiddleOutOrder 												X
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
			MyContainer() = default;
			// cctr
			MyContainer(const MyContainer& o) : data(o.data) { }
			// dtr
			~MyContainer() = default;

			/**
			 * @brief Assign operator, part of rule of 3
			 * 
			 * @param o The container
			 * @return MyContainer& 
			 */
			MyContainer& operator=(const MyContainer& o){
				if (this != &o){
					this->data = o.data;
				}
				return *this;
			}

			/**
			 * @brief Adding an object to the container
			 * 
			 * @param o The object that we want to add
			 */
			void add(const T& o){
				data.push_back(o);
			}

			/**
			 * @brief getting an object and removes from the container
			 * if the object does not exist - THROW
			 * if the object occurs 2+, remove all the entities
			 * 
			 * @param o 
			 */
			void remove(const T& o){
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
			 * @return size_t (unsigned int) 
			 */
			size_t size() const{
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
				for (size_t i = 0; i < container.data.size(); ++i) {
				os << container.data.at(i);
				if (i < container.data.size() - 1) {
					os << ", ";
					}
				}
				os<<"}";
				return os;
			}
	};
}