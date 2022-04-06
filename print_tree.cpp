#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include "srcs/map.hpp"
#include "srcs/vector.hpp"

template <typename T, typename Key, typename Compare = std::less<Key> >
class BinTree {
	struct cell_display {
		std::string   valstr;
		bool     present;
		cell_display() : present(false) {}
		cell_display(std::string valstr) : valstr(valstr), present(true) {}
	};

	typedef std::vector< std::string > string_vector;
	typedef std::vector< cell_display > display_row;
	typedef std::vector< display_row > display_rows;
	typedef ft::_node<ft::pair<const Key, T> > _node;

	_node *_root;
public:

	BinTree(_node *_root) : _root(_root) {}

	int get_max_depth() const { return _root ? _root->max_depth() : 0; }

	display_rows get_row_display() const {
		std::vector<_node*> traversal_stack;
		std::vector< std::vector<_node*> > rows;

		if(!_root) return display_rows();
	
		_node *p = _root;
		const int max_depth = _root->max_depth();
		rows.resize(max_depth);
		int depth = 0;
		for(;;) {
			if (depth == max_depth-1) {
				rows[depth].push_back(p);
				if(depth == 0) break;
				--depth;
				continue;
			}
			if (traversal_stack.size() == depth) {
				rows[depth].push_back(p);
				traversal_stack.push_back(p);
				if(p) p = p->left;
				++depth;
				continue;
			}
			if (rows[depth+1].size() % 2) {
				p = traversal_stack.back();
				if(p) p = p->right;
				++depth;
				continue;
			}
			if (depth == 0) break;
			traversal_stack.pop_back();
			p = traversal_stack.back();
			--depth;
		}

		display_rows rows_disp;
		std::stringstream ss;
		typename std::vector<std::vector<_node*> >::const_iterator it1 = rows.begin();
		while (it1 != rows.end()) {
			const std::vector<_node *> row = *it1;
			rows_disp.emplace_back();
			typename std::vector<_node *>::const_iterator it2 = row.begin();
			while (it2 != row.end()) {
				_node* pn = *it2;
				if (pn) {
					ss << pn->data;
					rows_disp.back().push_back(cell_display(ss.str()));
					ss = std::stringstream();
				} else {
					rows_disp.back().push_back(cell_display());
				}  
				++it2;
			}
			++it1;
		}
		return rows_disp;
	}
	string_vector row_formatter(const display_rows& rows_disp) const {

		std::string::size_type cell_width = 0;
		typename std::vector<display_row>::const_iterator it1 = rows_disp.begin();
		while (it1 != rows_disp.end()) {
			const display_row& row_disp = *it1;
			typename std::vector<cell_display>::const_iterator it2 = row_disp.begin();
			while (it2 != row_disp.end()) {
				const cell_display& cd = *it2;
				if (cd.present && cd.valstr.length() > cell_width) {
					cell_width = cd.valstr.length();
		   		}
				++it2;
			}
			++it1;
		}
		if (cell_width % 2 == 0) ++cell_width;
		if (cell_width < 3) cell_width = 3;
		string_vector formatted_rows;
		std::string::size_type row_count = rows_disp.size();
		std::string::size_type row_elem_count = 1 << (row_count-1);
		std::string::size_type left_pad = 0;
		for (std::string::size_type r = 0; r < row_count; ++r) {
			const display_row& cd_row = rows_disp[row_count-r-1];
			std::string::size_type space = (std::string::size_type(1) << r) * (cell_width + 1) / 2 - 1;
			std::string row;
			for (std::string::size_type c = 0; c < row_elem_count; ++c) {
				row += std::string(c ? left_pad*2+1 : left_pad, ' ');
				if (cd_row[c].present) {
					const std::string& valstr = cd_row[c].valstr;
					std::string::size_type long_padding = cell_width - valstr.length();
					std::string::size_type short_padding = long_padding / 2;
					long_padding -= short_padding;
					row += std::string(c%2 ? short_padding : long_padding, ' ');
					row += valstr;
					row += std::string(c%2 ? long_padding : short_padding, ' ');
				} else {
					row += std::string(cell_width, ' ');
				}
			}
			formatted_rows.push_back(row);
			if (row_elem_count == 1) break;
			std::string::size_type left_space  = space + 1;
			std::string::size_type right_space = space - 1;
			for (std::string::size_type sr = 0; sr < space; ++sr) {
				std::string row;
				for (std::string::size_type c = 0; c < row_elem_count; ++c) {
					if (c % 2 == 0) {
						row += std::string(c ? left_space*2 + 1 : left_space, ' ');
						row += cd_row[c].present ? '/' : ' ';
						row += std::string(right_space + 1, ' ');
					} else {
						row += std::string(right_space, ' ');
						row += cd_row[c].present ? '\\' : ' ';
					}
				}
				formatted_rows.push_back(row);
				++left_space;
				--right_space;
			}
			left_pad += space + 1;
			row_elem_count /= 2;
		}

		std::reverse(formatted_rows.begin(), formatted_rows.end());
	
		return formatted_rows;
	}

	static void trim_rows_left(string_vector& rows) {
		if(!rows.size()) return;
		std::basic_string<char>::size_type min_space = rows.front().length();

		typename std::vector<std::string>::const_iterator it1 = rows.begin();
		while (it1 != rows.end()) {
			const std::string& row = *it1;
			std::basic_string<char>::size_type i = row.find_first_not_of(' ');
			if(i==std::string::npos) i = row.length();
			if(i == 0) return;
			if(i < min_space) min_space = i;
			it1++;
		}
		typename std::vector<std::string>::iterator it2 = rows.begin();
		while (it2 != rows.end()) {
			std::string& row = *it2;
			row.erase(0, min_space);
			it2++;
	}   }

	void print(std::ostream &out) const {
		const int d = get_max_depth();
		if (d == 0) {
			out << " <empty tree>\n";
			return;
		}
		const display_rows rows_disp = get_row_display();
		string_vector formatted_rows = row_formatter(rows_disp);
		trim_rows_left(formatted_rows);
		typename std::vector<std::string>::const_iterator it1 = formatted_rows.begin();
		while (it1 != formatted_rows.end()) {
			const std::string& row = *it1;
			out << ' ' << row << '\n';
			++it1;
		}
	}
};

template <typename T, typename V>
void print_tree(ft::map<T, V> &map)
{
	BinTree<V, T> bt(map.get_tree()->get_root());
	bt.print(std::cout);
}

template <typename T, typename U>
std::ostream &operator<<(std::ostream &outputFile, const ft::map<T, U> &map)
{
	outputFile	<< "\033[1;36mSize\t" << map.size() << "\t\tMax Size\t" << map.max_size()
				<< "\033[0m" << std::endl
				<< "\033[1;36mContent ";
	if (map.empty())
		outputFile << "<empty>";
	else
	{

		typename ft::map<T, U>::const_iterator it = map.begin();
		while (true)
		{
			outputFile << it->first << "=" << it->second;
			if (++it != map.end())
				outputFile << ", ";
			else
				break;
		}
	}
	outputFile << "\033[0m";
	return outputFile;
}


int main() {

	ft::map<int, int> map1, map2;

	/*map1.insert(ft::pair<char,int>('a', 30));
	map1.insert(ft::pair<char,int>('c', 70));
	map1.insert(ft::pair<char,int>('b', 20));
	map1.insert(ft::pair<char,int>('d', 20));
	map1.insert(ft::pair<char,int>('P', 10));
	map1.insert(ft::pair<char,int>('e', 50));
	map1.insert(ft::pair<char,int>('Y', 50));
	map1.insert(ft::pair<char,int>('0', 101));
	map1.insert(ft::pair<char,int>('f', 40));
	map1.insert(ft::pair<char,int>('g', 60));
	map1.insert(ft::pair<char,int>('2', 100));
	map1.insert(ft::pair<char,int>('9', 100));

	std::cout << map1 << std::endl;
	print_tree(map1);

	map1.erase('b');
	std::cout << map1 << std::endl;
	print_tree(map1);

	map1.erase('c');
	std::cout << map1 << std::endl;
	print_tree(map1);

	map1.erase('W');
	std::cout << map1 << std::endl;
	print_tree(map1);

	map1.erase('0');
	std::cout << map1 << std::endl;
	print_tree(map1);

	map1.erase('e');
	std::cout << map1 << std::endl;
	print_tree(map1);

	map1.erase('f');
	std::cout << map1 << std::endl;
	print_tree(map1);

	map1.erase('g');
	std::cout << map1 << std::endl;
	print_tree(map1);*/


	std::cout << "Map Random Basic insert :" << std::endl;
	for (int i = 0; i < 20; ++i)
	{
		map1.insert(ft::pair<int,int>((rand() % 1000), i));
		//std::cout << "-------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		//print_tree(map1);
	}
	std::cout << map1 << std::endl;


	ft::map<int, int>::iterator one = map1.begin();
	while (one != map1.end())
	{
		std::cout << "Deleting " << one->first << std::endl;
		map1.erase((one++)->first);
		std::cout << map1 << std::endl;
		print_tree(map1);

		int i = 0;
		ft::map<int, int>::iterator one2 = map1.begin();
		while (one2 != map1.end())
		{
			one2++;
			i++;
		}
		if (i != map1.size())
		{
			std::cout << "ERROR" << std::endl;
			return 1;
		}
		std::cout << "-----------------------------------------------------" << std::endl;
	}
}
