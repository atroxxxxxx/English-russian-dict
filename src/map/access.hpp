#ifndef MAP_ACCESS_HPP
#define MAP_ACCESS_HPP

#include "declaration.hpp"

template< class Key, class Mapped, class Compare >
typename src::Map< Key, Mapped, Compare >::mapped_type&
src::Map< Key, Mapped, Compare >::at(const key_type& key)
{}
template< class Key, class Mapped, class Compare >
const typename src::Map< Key, Mapped, Compare >::mapped_type&
src::Map< Key, Mapped, Compare >::at(const key_type& key) const
{}
template< class Key, class Mapped, class Compare >
typename src::Map< Key, Mapped, Compare >::mapped_type&
src::Map< Key, Mapped, Compare >::operator[](const key_type& key)
{}
template< class Key, class Mapped, class Compare >
typename src::Map< Key, Mapped, Compare >::mapped_type&
src::Map< Key, Mapped, Compare >::operator[](key_type&& key)
{}

#endif
