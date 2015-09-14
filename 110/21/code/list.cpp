template <class T>
LinkedList<T>::LinkedList() : head(0) {
}

template <class T>
void LinkedList<T>::append(T d) {
	if (head == 0) {
		LinkedList<T>::Node *newNode = new LinkedList<T>::Node;
		newNode->data = d;
		newNode->next = 0;
		head = newNode;
	} else {
		LinkedList<T>::Node *newNode = new LinkedList<T>::Node;
		newNode->data = d;
		newNode->next = 0;

		LinkedList<T>::Node *current = head;
		while (current->next != 0)
			current = current->next;
		current->next = newNode;
	}
}

template <class T>
void LinkedList<T>::printContents() {
	LinkedList<T>::Node *current = head;
	while (current != 0) {
		cout << current->data << " ";
		current = current->next;
	}
   cout << endl;
}

template <class T>
void LinkedList<T>::insert(T d) {
	LinkedList<T>::Node *newNode, *current;

	newNode = new LinkedList<T>::Node;
	newNode->data = d;

	current = head;
	while (current && current->next && current->next->data < d) {
		current = current->next;
	}

   if (current == head && (!current || current->data > d)) {
         head = newNode;
         newNode->next = current;
   } else {
      newNode->next = current->next;
      current->next = newNode;
   }
}

template <class T>
void LinkedList<T>::remove(T d) {
	LinkedList<T>::Node  *current = head,
								*prev = 0;
	while (current && current->data != d) {
		prev = current;
		current = current->next;
	}

   if (head == 0 || current == 0) {
      return; // or throw an exception
   } else if (prev == 0) {
      head = current->next;
      delete current;
   } else {
      prev->next = current->next;
      delete current;
   }
}

template <class T>
T LinkedList<T>::get(int i) {
	LinkedList<T>::Node *current = head;
	while (i > 0 && current) {
		current = current->next;
		i--;
	}
	if (current) {
		return current->data;
	} else {
		throw "out of bounds or something";
	}
}

template <class T>
LinkedList<T>::~LinkedList() {
      LinkedList<T>::Node *tmp;
      while (!isEmpty()) {
         tmp = head->next;
         delete head;
         head = tmp;
      }
}
