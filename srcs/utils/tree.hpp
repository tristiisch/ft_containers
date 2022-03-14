/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tglory <tglory@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:36:17 by allanganoun       #+#    #+#             */
/*   Updated: 2022/03/14 21:13:16 by tglory           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template <class Key, class T>
	class tree
	{
		public :
			
			tree(Key key, T object) : key(key), object(object)
			{

			}

			tree(tree<Key, T> treeAtBase, Key key, T object) : key(key), object(object)
			{

			}

		private :
			Key key; // Clef
			T object; // Objet
			int depthSpace; // Profondeur du noeud
			int *bigTreeHeight; // Hauteur de l'arbre maximum actuellement

			tree<Key, T> *left; // Noeud Enfant Gauche
			tree<Key, T> *right; // Noeud Enfant Droite
			tree<Key, T> *parent; // Noeud Parent
	};
}
