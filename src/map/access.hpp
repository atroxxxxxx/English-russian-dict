#ifndef MAP_ACCESS_HPP
#define MAP_ACCESS_HPP

#include "declaration.hpp"
#include <exception>

template< class Key, class Mapped, class Compare >
typename src::Map< Key, Mapped, Compare >::mapped_type&
src::Map< Key, Mapped, Compare >::at(const key_type& key)
{
	iterator current = this->find(key);
	if (current == this->end())
	{
		throw std::out_of_range("element wasn't found");
	}
	return current->second;
}
template< class Key, class Mapped, class Compare >
const typename src::Map< Key, Mapped, Compare >::mapped_type&
src::Map< Key, Mapped, Compare >::at(const key_type& key) const
{
	return at(key);
}
template< class Key, class Mapped, class Compare >
typename src::Map< Key, Mapped, Compare >::mapped_type&
src::Map< Key, Mapped, Compare >::operator[](const key_type& key)
{
	iterator hint = this->end();
	hint = this->lower_bound(key);
	if ((hint == this->end()) || comp_(key, hint->first))
	{
		return this->insert(hint, new node_type{{key, {}}, true, this->get_data(hint)})->second;
	}
	return hint->second;
}
template< class Key, class Mapped, class Compare >
typename src::Map< Key, Mapped, Compare >::mapped_type&
src::Map< Key, Mapped, Compare >::operator[](key_type&& key)
{
	iterator hint = this->end();
	hint = this->lower_bound(key);
	if ((hint == this->end()) || comp_(key, hint->first))
	{
		return this->insert(hint, new node_type{{std::move(key), {}}, true, this->get_data(hint)})->second;
	}
	return hint->second;
}
#endif
