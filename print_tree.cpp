#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include "srcs/map.hpp"
#include "srcs/stack.hpp"
#include "srcs/utils/tree_iterator.hpp"
#include "srcs/vector.hpp"

template <typename T, typename Key, typename Compare = std::less<Key> >
class BinTree {
	ft::_node<ft::pair<const Key, T> > *_root;

public:
	struct cell_display {
		std::string   valstr;
		bool     present;
		cell_display() : present(false) {}
		cell_display(std::string valstr) : valstr(valstr), present(true) {}
	};

	typedef std::vector< std::vector< cell_display > > display_rows;

	BinTree() : _root(NULL) {}
	BinTree(ft::_node<ft::pair<const Key, T> > *_root) : _root(_root) {}

	int get_max_depth() const { return _root ? _root->max_depth() : 0; }

	display_rows get_row_display() const {
		std::vector<ft::_node<ft::pair<const Key, T> >*> traversal_stack;
		std::vector< std::vector<ft::_node<ft::pair<const Key, T> >*> > rows;
		if(!_root) return display_rows();
	
		ft::_node<ft::pair<const Key, T> > *p = _root;
		const int max_depth = _root->max_depth();
		rows.resize(max_depth);
		int depth = 0;
		for(;;) {
			if(depth == max_depth-1) {
				rows[depth].push_back(p);
				if(depth == 0) break;
				--depth;
				continue;
			}
			if(traversal_stack.size() == depth) {
				rows[depth].push_back(p);
				traversal_stack.push_back(p);
				if(p) p = p->left;
				++depth;
				continue;
			}
			if(rows[depth+1].size() % 2) {
				p = traversal_stack.back();
				if(p) p = p->right;
				++depth;
				continue;
			}
			if(depth == 0) break;
			traversal_stack.pop_back();
			p = traversal_stack.back();
			--depth;
		}

		display_rows rows_disp;
		std::stringstream ss;
		for(const auto& row : rows) {
			rows_disp.emplace_back();
			for(ft::_node<ft::pair<const Key, T> >* pn : row) {
				if(pn) {
					ss << pn->data;
					rows_disp.back().push_back(cell_display(ss.str()));
					ss = std::stringstream();
				} else {
					rows_disp.back().push_back(cell_display());
		}   }   }
		return rows_disp;
	}

	std::vector<std::string> row_formatter(const display_rows& rows_disp) const {
		using s_t = std::string::size_type;

		s_t cell_width = 0;
		for(const auto& row_disp : rows_disp) {
			for(const auto& cd : row_disp) {
				if(cd.present && cd.valstr.length() > cell_width) {
					cell_width = cd.valstr.length();
		}   }   }

		if(cell_width % 2 == 0) ++cell_width;
		if(cell_width < 3) cell_width = 3;
		std::vector<std::string> formatted_rows;
		s_t row_count = rows_disp.size();
		s_t row_elem_count = 1 << (row_count-1);
		s_t left_pad = 0;
		for(s_t r=0; r<row_count; ++r) {
			const auto& cd_row = rows_disp[row_count-r-1];
			s_t space = (s_t(1) << r) * (cell_width + 1) / 2 - 1;
			std::string row;
			for(s_t c=0; c<row_elem_count; ++c) {
				row += std::string(c ? left_pad*2+1 : left_pad, ' ');
				if(cd_row[c].present) {
					const std::string& valstr = cd_row[c].valstr;
					s_t long_padding = cell_width - valstr.length();
					s_t short_padding = long_padding / 2;
					long_padding -= short_padding;
					row += std::string(c%2 ? short_padding : long_padding, ' ');
					row += valstr;
					row += std::string(c%2 ? long_padding : short_padding, ' ');
				} else {
					row += std::string(cell_width, ' ');
				}
			}
			formatted_rows.push_back(row);
			if(row_elem_count == 1) break;
			s_t left_space  = space + 1;
			s_t right_space = space - 1;
			for(s_t sr=0; sr<space; ++sr) {
				std::string row;
				for(s_t c=0; c<row_elem_count; ++c) {
					if(c % 2 == 0) {
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

	static void trim_rows_left(std::vector<std::string>& rows) {
		if(!rows.size()) return;
		std::basic_string<char>::size_type min_space = rows.front().length();
		for (const auto& row : rows) {
			auto i = row.find_first_not_of(' ');
			if(i==std::string::npos) i = row.length();
			if(i == 0) return;
			if(i < min_space) min_space = i;
		}
		for(auto& row : rows) {
			row.erase(0, min_space);
	}   }

	void print(std::ostream &out) const {
		const int d = get_max_depth();
		if (d == 0) {
			out << " <empty tree>\n";
			return;
		}
		const display_rows rows_disp = get_row_display();
		std::vector<std::string> formatted_rows = row_formatter(rows_disp);
		trim_rows_left(formatted_rows);
		for (const auto& row : formatted_rows) {
			out << ' ' << row << '\n';
		}
	}
};


template <typename T, typename U, typename C>
std::ostream &operator<<(std::ostream &outputFile, const ft::tree<T, U, C> *tree)
{
	BinTree<int, char> bt(tree->get_root());
	bt.print(outputFile);
	return outputFile;
}



int main() {
	ft::map<char, int> map;

	map.insert(ft::pair<char,int>('a', 30));
	map.insert(ft::pair<char,int>('c', 70));
	map.insert(ft::pair<char,int>('b', 20));
	map.insert(ft::pair<char,int>('d', 10));
	map.insert(ft::pair<char,int>('e', 50));
	map.insert(ft::pair<char,int>('0', 101));
	map.insert(ft::pair<char,int>('f', 40));
	// map.insert(ft::pair<char,int>('g', 60));
	// map.insert(ft::pair<char,int>('2', 100));
	// map.insert(ft::pair<char,int>('W', 30));
	// map.insert(ft::pair<char,int>('P', 70));
	// map.insert(ft::pair<char,int>('G', 20));
	// map.insert(ft::pair<char,int>('E', 20));
	// map.insert(ft::pair<char,int>('S', 20));
	// map.insert(ft::pair<char,int>('+', 9));
	// map.insert(ft::pair<char,int>('N', 20));

	// map.insert(ft::pair<char,int>('A', 30));
	// map.insert(ft::pair<char,int>('c', 70));

	std::cout << map.get_tree() << std::endl;
}