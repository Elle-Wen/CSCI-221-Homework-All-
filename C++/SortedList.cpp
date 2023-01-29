#include "SortedList.hh"
#include <string>
using namespace std;

class Node{
	public:
		Node(string dataa){ //constructor 
			data = dataa;
			next = nullptr; 
		}
		~Node();
		string data;
		Node* next; 
};
class SortedList{
	public:
		Node* head;
		string sorting_type;
		SortedList(string sorting_typee){ //constructor 
			Node* head = nullptr; //start from empty list 
			string sorting_type = sorting_typee; 
		}
		~SortedList(){//deconstructor 
			this->remove_all();
		}
		SortedList* deep_copy() const{ //creating a deep copy of the object 
			SortedList* copy = new SortedList(sorting_type);
			string* values = this->only_data(); 
			int length = this->length();
			int i = 0; //index for length of the list 
			for (i;i<length;i++){
				copy->add_element(values[i]);
			}
			return copy; 
		}
		void add_element(string element){ //add a node according to sorting method 
			Node* new_node = new Node(element); //creating new node 
			if (sorting_type == "string length"){
				int len1=head->data.size();
				int len_element=element.size();
				if ((head == nullptr)||(len1 >= len_element)){ //if it is empty list or the new element is <= head node, then just assign to head
					new_node->next = head;
					head = new_node; 
					return;
				}
				else{ 
					Node* temp = head; 
					int len3=temp->next->data.size();
					while (temp->next != nullptr && len3 < len_element){
						temp = temp->next;
						len3=temp->next->data.size();
					}
					new_node->next = temp->next;
					temp->next = new_node;
				}
			}
			if (sorting_type == "ASCII"){
				if ((head == nullptr)||head->data>=element ){ //if it is empty list or the new element is <= head node, then just assign to head
					new_node->next = head;
					head = new_node; 
					return;
				}
				else{ 
					Node* temp = head; 
					while (temp->next != nullptr && temp->next->data < element){
						temp = temp->next;
					}
					new_node->next = temp->next;
					temp->next = new_node;
				}
			}
		}
		void remove_element(string element){ //remove all instance of an element 
			Node* node_to_delete;
			// if head stores element, keep ajdusting head 
			while (head!= nullptr && head->data == element){
				node_to_delete = head; 
				head = head->next;
				delete(node_to_delete);
			}
			// if not, traversing the list 
			Node* temp = head; 
			if (temp != nullptr){ //if temp = null, do nothing 
				while (temp->next != nullptr){
					if (temp->next->data == element){ //if next node's data is element, then delete the next node and adjust 
						node_to_delete = temp->next; 
						temp->next = temp->next->next;
						delete(node_to_delete);
					}
					else{ //if not, just update temp 
						temp = temp->next; 
					}
				}
			}
		}
		void remove_all(){ //remove all nodes 
			Node* node_to_delete;
			while (head != nullptr){
				node_to_delete = head;
				head = head->next; 
				delete(node_to_delete);
			}
		}
		bool is_sorting_method_length()const{
			if (sorting_type == "string length"){
				return true; 
			}
			return false;
		}
		bool is_sorting_method_ASCII()const{
			if (sorting_type == "ASCII"){
				return true;
			}
			return false; 
		}
		int length()const{
			int counter = 0;
			Node* temp = head; 
			while (temp != nullptr){
				counter ++;
				temp = temp -> next; 
			}
			return counter; 
		}
		string* only_data()const{ //return an array of strings (contains all the data in the linked list)
			int size = this -> length(); 
			string* new_array = new string [size]; 
			Node* temp = head; 
			int i = 0; //index for new_array 
			while (temp != nullptr){
				new_array[i] = temp->data; 
				i++;
				temp = temp->next; 
			}
			return new_array; 
		}
		string value_at_position(int position)const{ //return the string at position 
			string value = (this->only_data())[position];
			return value; 
		}
		void change_sorting_to_length(){ //change sorting method to by string length 
			sorting_type = "string length"; 
			string* values = this->only_data(); 
			int length = this->length();
			this->remove_all(); //emptying list 
			int i = 0; //index for length of the list 
			for (i;i<length;i++){
				this->add_element(values[i]);
			}
		}
		void change_sorting_to_ASCII(){ //change sorting method to by ASCII
			sorting_type = "ASCII"; 
			string* values = this->only_data(); 
			int length = this->length();
			this->remove_all(); //emptying list 
			int i = 0; //index for length of the list 
			for (i;i<length;i++){
				this->add_element(values[i]);
			}
		}
	private:
	protected:
};

int main(){
}