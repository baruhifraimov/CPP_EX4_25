#pragma once
/**
 * TODO:
 * ITERATORS:
 * 1. AscendingOrder												X
 * 2. DescendingOrder												X
 * 3. SideCrossOrder												X
 * 4. ReverseOrder 													X
 * 5. Order 														X
 * 6. MiddleOutOrder 												X
 * 
 * */
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

namespace ariel{
	
	template <typename T = int> class MyContainer{
		private:
			vector<T> data;
		public:
			// forward decleration to avoid 'unknown types'
			class Order;
			class AscendingOrder;
			class DescendingOrder;												
			class SideCrossOrder;												
			class ReverseOrder;												
			class MiddleOutOrder;
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
					throw std::invalid_argument("ERROR: Object does not exist\n");
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
				for (size_t i = 0; i < container.size(); ++i) {
				os << container.data.at(i);
				if (i < container.size() - 1) {
					os << ", ";
					}
				}
				os<<"}";
				return os;
			}

			/**
			 * @brief Retunrs the begining of the Order iterator
			 * 
			 * @return Order 
			 */
			Order begin_order(){
				return Order(this,0);
			}

			/**
			 * @brief Retunrs the end of the Order iterator
			 * 
			 * @return Order 
			 */
			Order end_order(){
				return Order(this, data.size());
			}

			/**
			 * @brief Retunrs the begining of the Ascending Order iterator
			 * 
			 * @return Order 
			 */
			AscendingOrder begin_ascending_order(){
				return AscendingOrder(this,0);
			}

			/**
			 * @brief Retunrs the end of the Ascending Order iterator
			 * 
			 * @return Order 
			 */
			AscendingOrder end_ascending_order(){
				return AscendingOrder(this, data.size());
			}

			/**
			 * @brief Retunrs the begining of the Descending Order iterator
			 * 
			 * @return Order 
			 */
			DescendingOrder begin_descending_order(){
				return DescendingOrder(this,0);
			}

			/**
			 * @brief Retunrs the end of the Descending Order iterator
			 * 
			 * @return Order 
			 */
			DescendingOrder end_descending_order(){
				return DescendingOrder(this, data.size());
			}

			/**
			 * @brief Retunrs the begining of the Reverse Order iterator
			 * 
			 * @return Order 
			 */
			ReverseOrder begin_reverse_order(){
				return ReverseOrder(this,0);
			}

			/**
			 * @brief Retunrs the end of the Reverse Order iterator
			 * 
			 * @return Order 
			 */
			ReverseOrder end_reverse_order(){
				return ReverseOrder(this, data.size());
			}

			/**
			 * @brief Retunrs the begining of the SideCrossOrder iterator
			 * 
			 * @return Order 
			 */
			SideCrossOrder begin_side_cross_order(){
				return SideCrossOrder(this,0);
			}

			/**
			 * @brief Retunrs the end of the SideCrossOrder iterator
			 * 
			 * @return Order 
			 */
			SideCrossOrder end_side_cross_order(){
				return SideCrossOrder(this, data.size()/2);
			}

				/**
			 * @brief Retunrs the begining of the MiddleOutOrder iterator
			 * 
			 * @return Order 
			 */
			MiddleOutOrder begin_middle_out_order(){
				return MiddleOutOrder(this,data.size()/2);
			}

			/**
			 * @brief Retunrs the end of the MiddleOutOrder iterator
			 * 
			 * @return Order 
			 */
			MiddleOutOrder end_middle_out_order(){
				return MiddleOutOrder(this, data.size());
			}

			class Order{
				private:
					MyContainer* container;
					size_t current_index;
				public:
					Order(MyContainer* cont, size_t index) : 	container(cont),
																current_index(index) {}
					Order(const Order& o) : container(o.container), 
											current_index(o.current_index) {}
					/**
					 * @brief Dereference operator
					 * 
					 * @return T&* the current element
					 */
					T& operator*(){
						return container->data.at(current_index);
					}
					
					/**
					 * @brief const Dereference operator 
					 * 
					 * @return const T& the current element in const
					 */
					const T& operator*() const {
						return container->data.at(current_index);
					}

					/**
					 * @brief Pre increment
					 * 
					 * @return Order& returns the exact Iterator
					 */
					Order& operator++(){
						++current_index;
						return *this;
					}

					/**
					 * @brief Post increment
					 * 
					 * @return Order, returns a copy of the last Iterator 
					 */
					Order operator++(int) {
						Order temp = *this;
						++(*this);
						return temp;
					}

					/**
					 * @brief Check if we got the same container and then check if we are positioned at the same index
					 * 
					 * @param o The other iterator
					 * @return true If equal
					 * @return false else
					 */
					bool operator==(const Order& o){
						return ((container == o.container) && (current_index == o.current_index));
					}

					/**
					 * @brief Check if we don't have the same container and then check if we don't index
					 * 
					 * @param o The other iterator
					 * @return true If not equal
					 * @return false else
					 */
					bool operator!=(const Order& o){
						return (!(*this == o));
					}

					/**
					 * @brief Copy operator, copies the container and the current index
					 * 
					 * @param o 
					 * @return Order& 
					 */
					Order& operator=(const Order& o){
						if(this != &o){ // safe check if we are the same object
							this->container = o.container;
							this->current_index = o.current_index;
						}

						return *this;
					}
			};

			class AscendingOrder{
				private:
					vector<T> sorted_data;
					size_t current_index;
				public:
					AscendingOrder( MyContainer* cont, size_t index) : current_index(index) {
						sorted_data = cont->data;
						sort(sorted_data.begin(), sorted_data.end());
					}

					AscendingOrder(const AscendingOrder& o) : 	sorted_data(o.sorted_data), 
																current_index(o.current_index) {
					}
					/**
					 * @brief Dereference operator
					 * 
					 * @return T&* the current element
					 */
					T& operator*(){
						return sorted_data.at(current_index);
					}
					
					/**
					 * @brief const Dereference operator 
					 * 
					 * @return const T& the current element in const
					 */
					const T& operator*() const {
						return sorted_data.at(current_index);
					}

					/**
					 * @brief Pre increment
					 * 
					 * @return Order& returns the exact Iterator
					 */
					AscendingOrder& operator++(){
						++current_index;
						return *this;
					}

					/**
					 * @brief Post increment
					 * 
					 * @return AscendingOrder, returns a copy of the last Iterator 
					 */
					AscendingOrder operator++(int) {
						AscendingOrder temp = *this;
						++(*this);
						return temp;
					}

					/**
					 * @brief Check if we got the same container and then check if we are positioned at the same index
					 * 
					 * @param o The other iterator
					 * @return true If equal
					 * @return false else
					 */
					bool operator==(const AscendingOrder& o){
						return ((sorted_data == o.sorted_data) && (current_index == o.current_index));
					}

					/**
					 * @brief Check if we don't have the same container and then check if we don't index
					 * 
					 * @param o The other iterator
					 * @return true If not equal
					 * @return false else
					 */
					bool operator!=(const AscendingOrder& o){
						return (!(*this == o));
					}

					/**
					 * @brief Copy operator, copies the container and the current index
					 * 
					 * @param o 
					 * @return AscendingOrder& 
					 */
					AscendingOrder& operator=(const AscendingOrder& o){
						if(this != &o){ // safe check if we are the same object
							this->sorted_data = o.sorted_data;
							this->current_index = o.current_index;
						}

						return *this;
					}
			};

			class DescendingOrder{
				private:
					vector<T> sorted_data;
					size_t current_index;
				public:
					DescendingOrder(MyContainer* cont, size_t index) : current_index(index) {
						sorted_data = cont->data;
						sort(sorted_data.begin(), sorted_data.end());
						reverse(sorted_data.begin(), sorted_data.end());
					}

					DescendingOrder(const DescendingOrder& o) : 	sorted_data(o.sorted_data), 
																current_index(o.current_index) {
					}
					/**
					 * @brief Dereference operator
					 * 
					 * @return T&* the current element
					 */
					T& operator*(){
						return sorted_data.at(current_index);
					}
					
					/**
					 * @brief const Dereference operator 
					 * 
					 * @return const T& the current element in const
					 */
					const T& operator*() const {
						return sorted_data.at(current_index);
					}

					/**
					 * @brief Pre increment
					 * 
					 * @return Order& returns the exact Iterator
					 */
					DescendingOrder& operator++(){
						++current_index;
						return *this;
					}

					/**
					 * @brief Post increment
					 * 
					 * @return DescendingOrder, returns a copy of the last Iterator 
					 */
					DescendingOrder operator++(int) {
						DescendingOrder temp = *this;
						++(*this);
						return temp;
					}

					/**
					 * @brief Check if we got the same container and then check if we are positioned at the same index
					 * 
					 * @param o The other iterator
					 * @return true If equal
					 * @return false else
					 */
					bool operator==(const DescendingOrder& o){
						return ((sorted_data == o.sorted_data) && (current_index == o.current_index));
					}

					/**
					 * @brief Check if we don't have the same container and then check if we don't index
					 * 
					 * @param o The other iterator
					 * @return true If not equal
					 * @return false else
					 */
					bool operator!=(const DescendingOrder& o){
						return (!(*this == o));
					}

					/**
					 * @brief Copy operator, copies the container and the current index
					 * 
					 * @param o 
					 * @return DescendingOrder& 
					 */
					DescendingOrder& operator=(const DescendingOrder& o){
						if(this != &o){ // safe check if we are the same object
							this->sorted_data = o.sorted_data;
							this->current_index = o.current_index;
						}

						return *this;
					}
			};

			class ReverseOrder{
				private:
				vector<T> sorted_data;
				size_t current_index;
			public:
				ReverseOrder(MyContainer* cont, size_t index) : current_index(index) {
					sorted_data = cont->data;
					reverse(sorted_data.begin(), sorted_data.end());
				}

				ReverseOrder(const ReverseOrder& o) : 	sorted_data(o.sorted_data), 
															current_index(o.current_index) {
				}
				/**
				 * @brief Dereference operator
				 * 
				 * @return T&* the current element
				 */
				T& operator*(){
					return sorted_data.at(current_index);
				}
				
				/**
				 * @brief const Dereference operator 
				 * 
				 * @return const T& the current element in const
				 */
				const T& operator*() const {
					return sorted_data.at(current_index);
				}

				/**
				 * @brief Pre increment
				 * 
				 * @return Order& returns the exact Iterator
				 */
				ReverseOrder& operator++(){
					++current_index;
					return *this;
				}

				/**
				 * @brief Post increment
				 * 
				 * @return ReverseOrder, returns a copy of the last Iterator 
				 */
				ReverseOrder operator++(int) {
					ReverseOrder temp = *this;
					++(*this);
					return temp;
				}

				/**
				 * @brief Check if we got the same container and then check if we are positioned at the same index
				 * 
				 * @param o The other iterator
				 * @return true If equal
				 * @return false else
				 */
				bool operator==(const ReverseOrder& o){
					return ((sorted_data == o.sorted_data) && (current_index == o.current_index));
				}

				/**
				 * @brief Check if we don't have the same container and then check if we don't index
				 * 
				 * @param o The other iterator
				 * @return true If not equal
				 * @return false else
				 */
				bool operator!=(const ReverseOrder& o){
					return (!(*this == o));
				}

				/**
				 * @brief Copy operator, copies the container and the current index
				 * 
				 * @param o 
				 * @return ReverseOrder& 
				 */
				ReverseOrder& operator=(const ReverseOrder& o){
					if(this != &o){ // safe check if we are the same object
						this->sorted_data = o.sorted_data;
						this->current_index = o.current_index;
					}

					return *this;
				}
			};

			class SideCrossOrder{
				private:
					vector<T> sorted_data;
					size_t left_index, right_index,current_index;
					bool turn_flag; // indicates the current index; if its left (true) or right (false)
				public:
					SideCrossOrder(const MyContainer* cont, size_t index) : current_index(index){
						sorted_data = cont->data;
						sort(sorted_data.begin(),sorted_data.end());
						turn_flag = true;
						left_index = 0;
						right_index = sorted_data.size()-1;
					}
					SideCrossOrder(const SideCrossOrder& o) : sorted_data(o.sorted_data), 
											current_index(o.current_index),
											left_index(o.left_index),
											right_index(o.right_index),
											turn_flag(o.turn_flag) {}
					/**
					 * @brief Dereference operator
					 * 
					 * @return T&* the current element
					 */
					T& operator*(){
						if(turn_flag){
							current_index = left_index;
						}else{
							current_index = right_index;
						}
						return sorted_data.at(current_index);
					}
					
					/**
					 * @brief const Dereference operator 
					 * 
					 * @return const T& the current element in const
					 */
					const T& operator*() const {
						if(turn_flag){
							current_index = left_index;
						}else{
							current_index = right_index;
						}
						return sorted_data.data.at(current_index);
					}

					/**
					 * @brief Pre increment
					 * 
					 * @return SideCrossOrder& returns the exact Iterator
					 */
					SideCrossOrder& operator++(){
						if(turn_flag){
							current_index = left_index++;
							turn_flag = false;
						}else{
							current_index = right_index--;
							turn_flag = true;
						}
						return *this;
					}

					/**
					 * @brief Post increment
					 * 
					 * @return SideCrossOrder, returns a copy of the last Iterator 
					 */
					SideCrossOrder operator++(int) {
						SideCrossOrder temp = *this;
						++(*this);
						return temp;
					}

					/**
					 * @brief Check if we got the same container and then check if we are positioned at the same index
					 * 
					 * @param o The other iterator
					 * @return true If equal
					 * @return false else
					 */
					bool operator==(const SideCrossOrder& o){
						return ((sorted_data == o.sorted_data) && (current_index == o.current_index));
					}

					/**
					 * @brief Check if we don't have the same container and then check if we don't index
					 * 
					 * @param o The other iterator
					 * @return true If not equal
					 * @return false else
					 */
					bool operator!=(const SideCrossOrder& o){
						return (!(*this == o));
					}

					/**
					 * @brief Copy operator, copies the container and the current index
					 * 
					 * @param o 
					 * @return SideCrossOrder& 
					 */
					SideCrossOrder& operator=(const SideCrossOrder& o){
						if(this != &o){ // safe check if we are the same object
							this->sorted_data = o.sorted_data;
							this->current_index = o.current_index;
						}

						return *this;
					}

			};

			class MiddleOutOrder{
				private:
					vector<T> sorted_data;
					size_t current_index, counter;
					bool turn_flag; // indicates the current index; if its left (true) or right (false)
				public:
					MiddleOutOrder(const MyContainer* cont, size_t index) : current_index(index){
						sorted_data = cont->data;
						counter = 0;
						turn_flag = true;
					}
					MiddleOutOrder(const MiddleOutOrder& o) : sorted_data(o.sorted_data), 
											current_index(o.current_index),
											counter(o.counter),
											turn_flag(o.turn_flag) {}

					/**
					 * @brief Dereference operator
					 * 
					 * @return T&* the current element
					 */
					T& operator*(){
						return sorted_data.at(current_index);
					}
					
					/**
					 * @brief const Dereference operator 
					 * 
					 * @return const T& the current element in const
					 */
					const T& operator*() const {
						return sorted_data.at(current_index);
					}

					/**
					 * @brief Pre increment
					 * 
					 * @return MiddleOutOrder& returns the exact Iterator
					 */
					MiddleOutOrder& operator++(){
						if(turn_flag){
							if(current_index - counter > 0){ // check if we not going out of bounds
							current_index -= ++counter;
							turn_flag = false;
							}else {
							current_index = sorted_data.size();
							}
						}else{
							if(current_index + counter < sorted_data.size()){ // check if we not going out of bounds again
							current_index += ++counter;
							turn_flag = true;
							}else {
								current_index = sorted_data.size();
							}
						}
						return *this;
					}

					/**
					 * @brief Post increment
					 * 
					 * @return MiddleOutOrder, returns a copy of the last Iterator 
					 */
					MiddleOutOrder operator++(int) {
						MiddleOutOrder temp = *this;
						++(*this);
						return temp;
					}

					/**
					 * @brief Check if we got the same container and then check if we are positioned at the same index
					 * 
					 * @param o The other iterator
					 * @return true If equal
					 * @return false else
					 */
					bool operator==(const MiddleOutOrder& o){
						return ((sorted_data == o.sorted_data) && (current_index == o.current_index));
					}

					/**
					 * @brief Check if we don't have the same container and then check if we don't index
					 * 
					 * @param o The other iterator
					 * @return true If not equal
					 * @return false else
					 */
					bool operator!=(const MiddleOutOrder& o){
						return (!(*this == o));
					}

					/**
					 * @brief Copy operator, copies the container and the current index
					 * 
					 * @param o 
					 * @return MiddleOutOrder& 
					 */
					MiddleOutOrder& operator=(const MiddleOutOrder& o){
						if(this != &o){ // safe check if we are the same object
							this->sorted_data = o.sorted_data;
							this->current_index = o.current_index;
						}

						return *this;
					}

			};
	};
}