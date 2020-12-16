//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_DETAIL_BASE_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_DETAIL_BASE_HPP

#include <boost/gil/extension/io/png/tags.hpp>

#include <boost/assert.hpp>

#include <memory>

namespace boost { namespace gil { namespace detail {

struct png_ptr_wrapper
{
    png_ptr_wrapper()
    : _struct( nullptr )
    , _info  ( nullptr )
    {}

    png_structp _struct;
    png_infop   _info;
};

///
/// Wrapper for libpng's png_struct and png_info object. Implements value semantics.
///
struct png_struct_info_wrapper
{
protected:

    using png_ptr_t = std::shared_ptr<png_ptr_wrapper>;

protected:

    ///
    /// Default Constructor
    ///
    png_struct_info_wrapper( bool read = true )
    : _png_ptr( new png_ptr_wrapper()
              , ( ( read ) ? png_ptr_read_deleter : png_ptr_write_deleter )
              )
    {}

    png_ptr_wrapper*       get()       { return _png_ptr.get(); }
    png_ptr_wrapper const* get() const { return _png_ptr.get(); }

    png_struct*       get_struct()       { return get()->_struct; }
    png_struct const* get_struct() const { return get()->_struct; }

    png_info*       get_info()       { return get()->_info; }
    png_info const* get_info() const { return get()->_info; }

private:

    static void png_ptr_read_deleter( png_ptr_wrapper* png_ptr )
    {
        if( png_ptr )
        {
            if( png_ptr->_struct && png_ptr->_info )
            {
                png_destroy_read_struct( &png_ptr->_struct
                                       , &png_ptr->_info
                                       , nullptr
                                       );
            }

            delete png_ptr;
            png_ptr = nullptr;
        }
    }

    static void png_ptr_write_deleter( png_ptr_wrapper* png_ptr )
    {
        if( png_ptr )
        {
            if( png_ptr->_struct && png_ptr->_info )
            {
                png_destroy_write_struct( &png_ptr->_struct
                                        , &png_ptr->_info
                                        );
            }

            delete png_ptr;
            png_ptr = nullptr;
        }
    }


private:

    png_ptr_t _png_ptr;
};

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* base.hpp
D5AzBcRm+rB/PtuQ195BP0zj/Tnct3kheF3MVwzQRs53ppjwSxvkbWdkzefQz1no2pmrkdProK215LkpEfloJTJnqEeuuRiZUQ8dh67Z0JL8S/ebcssa9DxjLaXNZfmGXEJfy5E7ZbeZ0hE+/bgt78LL/ZG1dWjTKEXk215Ebk4y5cZzkU/g6c6/EydeAx3zdwdk2o6NwPpd+phnSD/W/sp4dMAeU5YuJqKL7J98tkdKPoN+vjckDx30aiz8DV5fHGrKfvRxu8fQd9DClL7kg0IfXoGMXwa9bYMHz5wt8mAjU1Z3Rn4gq2LQ3TcNZu89lXwEOz02PIxLkWlBU6agKy6/H5yjo4KdwBc5B4qQ4d9lGXIyfX3yrUfirPsePgJ+4PvAOpEXhxjyDvj4rb5HCu805Wj0aLM76OMl+oL3n8xEN9zpkWWbkQcb4Ulot9eL2Bmr0UlLTXkO2jvuryJXPQqPopfefoxvvbcb0vR1U2KY+5K+phz3FHLvafraB34T0Dc9+CLhWI/cxhrGIc9HfoU8hz6nFBny1ufwO/30yjSlEphdFSCX1mXIzw7oulRk5UDkCLQz4ib0WStssqWGXAt8Z46BphdAp/s9cvbVyN6f4fkTDDm/2DqnBf80Rzdj46z5DRl1iiFjG7PXfDrzRtZuyvVIo670hX30KXP7/QtkPPryXRM5C58G+1sfLUNLJ7OX8gpnJoqhsTK+BUKGdfsWvkJGHbMPek5jX/Imckgw3695vh0cBLEpX2+BnoUf7moLLT9pMFdTGqPjT9hmyLwbTXniKlM+B/bPNjal7VXAeie2Yzky6mq+HW4E3O9A1mGTnB7nkUUb+Jb2dWyeccCwJzzwEf0Ao18fxiai/qUn4CnmlQBvpnhF0u4zJPdZU473oIeY07wsU9KQ3+cwrhcaGHgxcEFOJNNuQ2/kCbSw6hRos9CUImR4G/AX7OWRftD+H72Qj9i3D+5A7nZB1v0VvgdW91wM76Gvv4fPTsuAFwejY1hbTiNkxFKRxfuxW/OQv8nQ8HDoH577FPtO1iLD0Ec7zjHkfXTPxonYwdjUja/CnkhDxgOX9zYB3yJk9hLOT6Aj5iFDf/2aed2L/XsJfTZg/WdiO/nZEXkYWx6ZcfJycmxtw0a9BN5iPt0XoosuwD6cDy9fg355Hnv0HG4jQjedNFHEd70pi9Hr76JbrwbnH9xuyHPY94N7wNc3iZSehSx/A1mXgY0I728tQ64hp15oaMhFd3tkzmIDW8iUzanI+Rz2fe9CloY4I4R+vht8NlntkWnr4JVN9AG9P7ISfDG/93sjB94zZG09aG0UfsTj4PoHvhf+EVgfa8ijyI+zN2Abn0Q/b5Jv+VFoohu6FjnX1wOdYrNsOp45Y0M1bmbKfXNFBn3MnS6seR02QmFPQyrgi09nQVfYTombkdsPkpPxaUOG3oUNy1zWPYfN8oMpX2AzDGcuD/TxyDvYLX9s5GQ5OGt3AXfSYP8sQ67VzzZl3SRoaCX6izk0of1Dq4AnsqLBPOxH/IQFBeiu3ciJZ/kBhguGe+TREtb2rEe6Y8u1+LvIFQ2hS+zeG3Ygt5j/b9ifb34i8rcJ6MJWHlkD7X6IbXEbflX3VxjjY+TdYr6VZ+zkb6GDpyi7x0S3CTYza6SdvzN8Nxt4JCM3OpjydoA8fcBudxPWeIsp3Y7D98GGTX4Xe+MS6KMl9IGtOQE5cGF/U56GBv6OXp2MjL6gKzrURNbvgT+fJF9aOrTSmtyPPYHHLuYATr3wGKaKPP2tKXMOgNs0ePEZ7trh74/hrUk5pvTZacr1i5jTgx4Zhg83FxjOXw+9rEYfraVtA+CO7psBHMfsEfnuO+g=
*/