#ifndef VSET_VTREE_ARRAY_HPP
#define VSET_VTREE_ARRAY_HPP

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <iterator>
//#include <fas/typemanip/remove_const.hpp>

namespace vset{ 

template<typename T, size_t N>
class array
{
public:
  enum { dimension = N};
  typedef T value_type;
  //typedef typename fas::remove_const<T>::type data_type[N];
  typedef value_type data_type[N];
  typedef size_t size_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef pointer iterator;
  typedef const_pointer const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef const std::reverse_iterator<iterator> const_reverse_iterator;
  typedef std::ptrdiff_t difference_type;

  array()
    : _size()
    , _data()
  {
  }

  reference operator[](size_type n)
  {
    return this->at(n);
  }

  const_reference operator[](size_type n) const
  {
    return this->at(n);
  }

  const_reference at ( size_type n ) const
  {
    if ( n < _size)
      return _data[n];
    throw std::out_of_range("array::at");
  }

  reference at ( size_type n )
  {
    if ( n < _size )
      return _data[n];
    throw std::out_of_range("array::at");
  }
  
  reference front ( )
  {
    if ( _size==0 )
      throw std::out_of_range("array::at");
    return _data[0];
  }
  
  const_reference front ( ) const
  {
    if ( _size==0 )
      throw std::out_of_range("array::at");
    return _data[0];
  }
  
  reference back ( )
  {
    if ( _size==0 )
      throw std::out_of_range("array::at");
    return _data[_size-1];
  }
  
  const_reference back ( ) const
  {
    if ( _size==0 )
      throw std::out_of_range("array::at");
    return _data[_size-1];
  }

  size_type size() const
  {
    return _size;
  }
  
  size_type max_size() const
  {
    return N;
  }
  
  size_type capacity() const
  {
    return N;
  }
  
  bool empty () const
  {
    return _size==0;
  }
  
  bool filled () const
  {
    return _size == N;
  }
  
  void resize ( size_type sz, T value = value_type() )
  {
    if (sz > _size)
      std::fill_n( end(), sz - _size, value );
    _size = sz;
  }
  
  void reserve ( size_type n ) {}

  reverse_iterator rbegin()
  {
    return reverse_iterator(end());
  }
  
  const_reverse_iterator rbegin() const
  {
    return const_reverse_iterator( end() );
  }

  reverse_iterator rend()
  {
    return reverse_iterator( begin() );
  }
  
  const_reverse_iterator rend() const
  {
    return const_reverse_iterator( begin() );
  }

  iterator begin()
  {
    return _data;
  }
  
  const_iterator begin() const
  {
    return _data;
  }
  
  iterator end()
  {
    return _data + _size;
  }
  
  const_iterator end() const
  {
    return _data + _size;
  }

#ifdef __GXX_EXPERIMENTAL_CXX0X__

  const reverse_iterator crbegin() const
  {
    return const_reverse_iterator(cend());
  }

  const_reverse_iterator crend() const
  {
    return const_reverse_iterator( begin() );
  }

  const_iterator cbegin() const
  {
    return _data;
  }

  const_iterator cend() const
  {
    return _data + _size;
  }

#endif

  iterator last()
  {
    return _data + _size - 1;
  }
  
  const_iterator last() const
  {
    return _data  + _size - 1;
  }

  void clear()
  {
    _size = 0;
  }

  template <class InputIterator>
  void assign ( InputIterator first, InputIterator last )
  {
    std::copy( first, last, _data );
    _size = std::distance(first, last);
  }

  void assign ( size_type n, const T& u )
  {
    std::fill_n( begin(), n, u );
    _size = n;
  }

  void push_back ( const T& x )
  {
    _data[_size++] = x;
  }

  void pop_back ( )
  {
    --_size;
  }

  iterator insert ( iterator position, const T& x )
  {
    if ( this->size() + 1 > this->max_size() )
      throw std::out_of_range("array::insert");

    iterator first = position;
    iterator last = this->end();
    iterator d_last = last+1;
    while (first != last)
    {
        *(--d_last) = *(--last);
    }

    *position = x;
    ++_size;
    return position;
  }

  void insert ( iterator position, size_type n, const T& x )
  {
    if ( this->size() + n > this->max_size() )
      throw std::out_of_range("array::insert");
    std::copy_backward(position, end(), end()+n);
    std::fill_n(position, n, x);
    _size+=n;
  }

  template <class InputIterator>
  void insert ( iterator position, InputIterator first, InputIterator last )
  {
    difference_type dist = std::distance(first,last);
    if (dist<=0)
      return;
    if ( this->size() + dist > this->max_size() )
      throw std::out_of_range("array::insert");

    std::copy_backward(position, end(), end()+dist );
    std::copy(first, last, position);
    _size+=dist;
  }

#ifdef __GXX_EXPERIMENTAL_CXX0X__

  iterator erase ( const_iterator position )
  {
    if ( position == this->cend() )
      throw std::out_of_range("iterator array<>::erase ( iterator position )");
    
    std::copy( position + 1, this->end(), position);
    this->resize( _size - 1 );
    return position;
  }
  
#else

  iterator erase ( iterator position )
  {
    if ( position == this->end() )
      throw std::out_of_range("iterator array<>::erase ( iterator position )");

    std::copy( position + 1, this->end(), position);
    this->resize( _size - 1 );
    return position;
  }
  
#endif

  iterator erase ( iterator first, iterator last )
  {
    difference_type dist = std::distance(first,last);;
    std::copy( last, this->end(), first);
    this->resize( _size - dist );
    return first;
  }

private:
  
  size_type _size;
  data_type _data;
};

}

#endif
