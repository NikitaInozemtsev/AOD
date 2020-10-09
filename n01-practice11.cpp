#include<iostream>
#include<string>

struct Person
{
	std::string number;
	std::string adress;
};
int HashFunctionHorner(const std::string& s, int table_size, const int key)
{
	int hash_result = 0;
	for (int i = 0; s[i] != 0; ++i)
	{
		hash_result = (key * hash_result + s[i]) % table_size;
	}
	hash_result = (hash_result * 2 + 1) % table_size;
	return hash_result;
}

struct HashFunction1
{
	int operator()(const std::string& s, int table_size) const
	{
		return HashFunctionHorner(s, table_size, table_size - 1);
	}

};

struct HashFunction2
{
	int operator()(const std::string& s, int table_size) const
	{
		return HashFunctionHorner(s, table_size, table_size + 1);
	}
};

template <class T, class THash1 = HashFunction1, class THash2 = HashFunction2>

class HashTable

{
public:
	static const int default_size = 8;
	constexpr static const double rehash_size = 0.75;
	struct Node
	{
		T value;
		bool state;
		Node(const T& value_) : value(value_), state(true) {}
	};
	Node** arr;
	int size;
	int buffer_size;
	int size_all_non_NULL;
	void Out() {
		for (int i = 0; i < buffer_size; i++) {
			if (arr[i] != NULL) {
				std::cout << arr[i]->value.number << " " << arr[i]->value.adress << " " << i;
				std::cout << "\n";
			}
		}
	}
	void Resize()
	{
		int past_buffer_size = buffer_size;
		buffer_size *= 2;
		size_all_non_NULL = 0;
		size = 0;
		Node** arr2 = new Node * [buffer_size];
		for (int i = 0; i < buffer_size; ++i)
			arr2[i] = NULL;
		std::swap(arr, arr2);
		for (int i = 0; i < past_buffer_size; ++i)
		{
			if (arr2[i] && arr2[i]->state)
				Add(arr2[i]->value);
		}
		for (int i = 0; i < past_buffer_size; ++i)
			if (arr2[i])
				delete arr2[i];
		delete[] arr2;
	}

	void Rehash()
	{
		size_all_non_NULL = 0;
		size = 0;
		Node** arr2 = new Node * [buffer_size];
		for (int i = 0; i < buffer_size; ++i)
			arr2[i] = NULL;
		std::swap(arr, arr2);
		for (int i = 0; i < buffer_size; ++i)
		{
			if (arr2[i] && arr2[i]->state)
				Add(arr2[i]->value);
		}
		for (int i = 0; i < buffer_size; ++i)
			if (arr2[i])
				delete arr2[i];
		delete[] arr2;
	}

	HashTable()

	{

		buffer_size = default_size;

		size = 0;

		size_all_non_NULL = 0;

		arr = new Node * [buffer_size];

		for (int i = 0; i < buffer_size; ++i)

			arr[i] = NULL;

	}

	~HashTable()

	{

		for (int i = 0; i < buffer_size; ++i)

			if (arr[i])

				delete arr[i];

		delete[] arr;

	}

	bool Add(const T& value, const THash1& hash1 = THash1(), const THash2& hash2 = THash2())

	{

		if (size + 1 > int(rehash_size * buffer_size))

			Resize();

		else if (size_all_non_NULL > 2 * size)

			Rehash();

		int h1 = hash1(value.number, buffer_size);

		int h2 = hash2(value.number, buffer_size);

		int i = 0;

		int first_deleted = -1;

		while (arr[h1] != NULL && i < buffer_size)

		{

			if (arr[h1]->value.number == value.number && arr[h1]->state)

				return false;

			if (!arr[h1]->state && first_deleted == -1)

				first_deleted = h1;

			h1 = (h1 + h2) % buffer_size;

			++i;

		}

		if (first_deleted == -1)

		{

			arr[h1] = new Node(value);

			++size_all_non_NULL;

		}

		else

		{

			arr[first_deleted]->value.number = value.number;

			arr[first_deleted]->state = true;

		}

		++size;

		return true;

	}

	bool Remove(const T& value, const THash1& hash1 = THash1(), const THash2& hash2 = THash2())

	{

		int h1 = hash1(value.number, buffer_size);

		int h2 = hash2(value.number, buffer_size);

		int i = 0;

		while (arr[h1] != NULL && i < buffer_size)

		{

			if (arr[h1]->value.number == value.number && arr[h1]->state)

			{

				arr[h1]->state = false;

				arr[h1] = NULL;

				--size;

				return true;
			}
			h1 = (h1 + h2) % buffer_size;
			++i;
		}
		return false;
	}

	bool Find(const T& value, const THash1& hash1 = THash1(), const THash2& hash2 = THash2())
	{
		int h1 = hash1(value.number, buffer_size);
		int h2 = hash2(value.number, buffer_size);
		int i = 0;
		while (arr[h1] != NULL && i < buffer_size)
		{
			if (arr[h1]->value.number == value.number && arr[h1]->state)
				return true;
			h1 = (h1 + h2) % buffer_size;
			++i;
		}
		return false;
	}
};

int main(void) {
	setlocale(LC_ALL, "rus");
	HashTable<Person> h;
	std::string buff;
	while (true)
	{
		std::cout << "vvod: ";
		std::cin >> buff;
		if (buff == "n") { break; }
		Person person;
		person.number = buff;
		std::cout << "adress: ";
		std::cin >> buff;
		person.adress = buff;
		h.Add(person);
	}
	Person p;
	p.number = "31";
	h.Remove(p);
	h.Out();
	system("pause");
}