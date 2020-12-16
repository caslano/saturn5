//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SCATTER_HPP
#define BOOST_COMPUTE_ALGORITHM_SCATTER_HPP

#include <boost/static_assert.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class MapIterator, class OutputIterator>
class scatter_kernel : meta_kernel
{
public:
    scatter_kernel() : meta_kernel("scatter")
    {}

    void set_range(InputIterator first,
                   InputIterator last,
                   MapIterator map,
                   OutputIterator result)
    {
        m_count = iterator_range_size(first, last);
        m_input_offset = first.get_index();
        m_output_offset = result.get_index();

        m_input_offset_arg = add_arg<uint_>("input_offset");
        m_output_offset_arg = add_arg<uint_>("output_offset");

        *this <<
            "const uint i = get_global_id(0);\n" <<
            "uint i1 = " << map[expr<uint_>("i")] << 
                " + output_offset;\n" <<
            "uint i2 = i + input_offset;\n" <<
            result[expr<uint_>("i1")] << "=" << 
                first[expr<uint_>("i2")] << ";\n";
    }

    event exec(command_queue &queue)
    {
        if(m_count == 0) {
            return event();
        }

        set_arg(m_input_offset_arg, uint_(m_input_offset));
        set_arg(m_output_offset_arg, uint_(m_output_offset));

        return exec_1d(queue, 0, m_count);
    }

private:
    size_t m_count;
    size_t m_input_offset;    
    size_t m_input_offset_arg;    
    size_t m_output_offset;    
    size_t m_output_offset_arg;    
};

} // end detail namespace

/// Copies the elements from the range [\p first, \p last) to the range
/// beginning at \p result using the output indices from the range beginning
/// at \p map.
///
/// Space complexity: \Omega(1)
///
/// \see gather()
template<class InputIterator, class MapIterator, class OutputIterator>
inline void scatter(InputIterator first,
                    InputIterator last,
                    MapIterator map,
                    OutputIterator result,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<MapIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    detail::scatter_kernel<InputIterator, MapIterator, OutputIterator> kernel;
    
    kernel.set_range(first, last, map, result);
    kernel.exec(queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SCATTER_HPP

/* scatter.hpp
fdH8LbT/DjfiDDG/w/ej8EMcdogNz5bhEuqHLUJk+q0k3XWEkdYGFK5EeB8Kz+ewkVZfSqvN7veBfw/2oriPUdhr2rk+f26kVUppRTktXQAyrUSY/hwC3XLw0RT3StwhA2DdOqjHyeJY8IW4wveXea9MRLvXQJo8JPjbuAbmPtGQpd+vd7bZx8cabdpi8x3dZvObHs383U226oKuczl5ToP7xpJiQRjL98IWIond+V5I7RzWOyCs4xbI1FdwbZK7GQVqMdPZImM/MPTa0vTS29jQi6bppbefoeex6Bm/Ics9ybbwZPkNOZbiiZTf0Bld18akt0+zTfs027RPs037NKe1zyjjWbZEEKZCyiH1fO9Gz065d2P+g7t99mL9jWSY6ugcCg/r7v7kOIMpPADhuRTe3PY+3BnpnkE6YyjsNfJFzVcgTo40PscX3c1/cGM4vDPsFuaz1qmkNzz5HfoXPO/K55dbKU8hYBfXOc8v9jX2KmNwnb+drHPfdrtN9U1pnjJVAPZ1bujnd1vHrGNbp15LOkZfrunB/KEst9Omnsps6qnSZlwwnutlQakgTITIP4dzvSzheuFGRfXsntzRrfv64XgDzO/wXyk8sLv64jjlFJb3wwoKV3XbJ5dzX6f6NPPtZ/5+N6A+J9SIv6zvdc3t2s3V/n3ryHekud07X5v27fOvHL3xNs8uqvg9OGS2Wke+tteRy7nao433BfyuYi6kBIJohBN5nfdJ4AHgM8EDpR5Y9sfTwNXgU8Eevj4GfDK4lsMTOLwN+BTwDnx9Jw5LO5YJHl/zWH8urztfIpJAXkfL8BDwMPBG4JHgjTmfYeCtwcPBjeAR4GbwZuDp4M3BfvAocCt4DHg2eCtwFDwOjDKKCWCZdz34avA24FvB24JvB28Pvgc8GTxf1hn4afCu4DfBu4PfF0DpsqM/lmEu357gFeBp4JXg6cZcuTEm5bFq+lz5dtAr4ny/o8+NcReYw6WQ41l/H+j1A+8HHgT2gYeA/eAR4AB4LLgVjDKKWeAp4BDX12zw7uAI19uBYKQlEuAA+CCutzngw8FHsF0eKVwO6h9pe1zGZDk4nb4yHY53r/kMjrEBxyuH3MLxbmP77wBvDr4LPBH8MHgy+BGwV44f2b7HwbPAT4EPBT8DPg68kNv1OfCl4OfBN4FfAiNt8Qr4SfAiMOKI18HvgN8Cv5fsh9Sen4IhYinbPxiyO5d7LNvv4DJIvM16XuNZBjyV9Qohjax3JfRknKv4frqa+/e1YA/3pzEyzO12naX/vM3p5mfoP/OgJ4ALWX8yZAnrT2T9Aur3SXzH9/n3fJ//zPd5J3g4eCW4lsNhR5fvxsL+LrEE0gkpr3CJzSCTIWGI4ddxGv5uAS9y4LOR+eTf0ZjjEjrE6ucxH3rpvh4Nm696dufTkBeh69w68z4RHbmujD4fXyKOxe+D3g4t4LM97fw/FiItqw/IIojhA7KsMNUHxDk6sx9IZZ4roy+IcwDqCzIdMhfyIOQHSHmlSzRCWiCHVCpfEQUFBQUFBYW/D71x/l+Xv3osueHfP3QNwFajBL03ef8f+N5EvR9Zu+9HnJbxTWclnsfXxXM6pBEyA6JDToNcA7H6rmNck3U80zWW6dled5bxS/rYpcd+6zxe+VP+6goKCgoKCgoKCgoK/0/0xv5/CT0UDulz1tj3f4hwkX9EG/n+h+KWJfhBnz8u1xiIYdC5F+P8WtI5oD2YCGu8Dz8sPySk+3T/zLAmNmc9byY934GJUGC2z6IuRnHem3WfrtWkXntP8R4Mmck+Mwt5+FYhkugP+Rzxz+3gPQPQQL5WfxxLEbRAe1DzRdtDsiknHNQeCg6uxue4Hh4=
*/