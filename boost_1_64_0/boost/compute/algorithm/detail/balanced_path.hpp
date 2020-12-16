//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_BALANCED_PATH_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_BALANCED_PATH_HPP

#include <iterator>

#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Balanced Path kernel class
///
/// Subclass of meta_kernel to break two sets into tiles according
/// to their balanced path.
///
class balanced_path_kernel : public meta_kernel
{
public:
    unsigned int tile_size;

    balanced_path_kernel() : meta_kernel("balanced_path")
    {
        tile_size = 4;
    }

    template<class InputIterator1, class InputIterator2,
             class OutputIterator1, class OutputIterator2,
             class Compare>
    void set_range(InputIterator1 first1,
                   InputIterator1 last1,
                   InputIterator2 first2,
                   InputIterator2 last2,
                   OutputIterator1 result_a,
                   OutputIterator2 result_b,
                   Compare comp)
    {
        typedef typename std::iterator_traits<InputIterator1>::value_type value_type;

        m_a_count = iterator_range_size(first1, last1);
        m_a_count_arg = add_arg<uint_>("a_count");

        m_b_count = iterator_range_size(first2, last2);
        m_b_count_arg = add_arg<uint_>("b_count");

        *this <<
            "uint i = get_global_id(0);\n" <<
            "uint target = (i+1)*" << tile_size << ";\n" <<
            "uint start = max(convert_int(0),convert_int(target)-convert_int(b_count));\n" <<
            "uint end = min(target,a_count);\n" <<
            "uint a_index, b_index;\n" <<
            "while(start<end)\n" <<
            "{\n" <<
            "   a_index = (start + end)/2;\n" <<
            "   b_index = target - a_index - 1;\n" <<
            "   if(!(" << comp(first2[expr<uint_>("b_index")],
                              first1[expr<uint_>("a_index")]) << "))\n" <<
            "       start = a_index + 1;\n" <<
            "   else end = a_index;\n" <<
            "}\n" <<
            "a_index = start;\n" <<
            "b_index = target - start;\n" <<
            "if(b_index < b_count)\n" <<
            "{\n" <<
            "   " << decl<const value_type>("x") << " = " <<
                        first2[expr<uint_>("b_index")] << ";\n" <<
            "   uint a_start = 0, a_end = a_index, a_mid;\n" <<
            "   uint b_start = 0, b_end = b_index, b_mid;\n" <<
            "   while(a_start<a_end)\n" <<
            "   {\n" <<
            "       a_mid = (a_start + a_end)/2;\n" <<
            "       if(" << comp(first1[expr<uint_>("a_mid")], expr<value_type>("x")) << ")\n" <<
            "           a_start = a_mid+1;\n" <<
            "       else a_end = a_mid;\n" <<
            "   }\n" <<
            "   while(b_start<b_end)\n" <<
            "   {\n" <<
            "       b_mid = (b_start + b_end)/2;\n" <<
            "       if(" << comp(first2[expr<uint_>("b_mid")], expr<value_type>("x")) << ")\n" <<
            "           b_start = b_mid+1;\n" <<
            "       else b_end = b_mid;\n" <<
            "   }\n" <<
            "   uint a_run = a_index - a_start;\n" <<
            "   uint b_run = b_index - b_start;\n" <<
            "   uint x_count = a_run + b_run;\n" <<
            "   uint b_advance = max(x_count / 2, x_count - a_run);\n" <<
            "   b_end = min(b_count, b_start + b_advance + 1);\n" <<
            "   uint temp_start = b_index, temp_end = b_end, temp_mid;" <<
            "   while(temp_start < temp_end)\n" <<
            "   {\n" <<
            "       temp_mid = (temp_start + temp_end + 1)/2;\n" <<
            "       if(" << comp(expr<value_type>("x"), first2[expr<uint_>("temp_mid")]) << ")\n" <<
            "           temp_end = temp_mid-1;\n" <<
            "       else temp_start = temp_mid;\n" <<
            "   }\n" <<
            "   b_run = temp_start - b_start + 1;\n" <<
            "   b_advance = min(b_advance, b_run);\n" <<
            "   uint a_advance = x_count - b_advance;\n" <<
            "   uint star = convert_uint((a_advance == b_advance + 1) " <<
                                            "&& (b_advance < b_run));\n" <<
            "   a_index = a_start + a_advance;\n" <<
            "   b_index = target - a_index + star;\n" <<
            "}\n" <<
            result_a[expr<uint_>("i")] << " = a_index;\n" <<
            result_b[expr<uint_>("i")] << " = b_index;\n";

    }

    template<class InputIterator1, class InputIterator2,
             class OutputIterator1, class OutputIterator2>
    void set_range(InputIterator1 first1,
                   InputIterator1 last1,
                   InputIterator2 first2,
                   InputIterator2 last2,
                   OutputIterator1 result_a,
                   OutputIterator2 result_b)
    {
        typedef typename std::iterator_traits<InputIterator1>::value_type value_type;
        ::boost::compute::less<value_type> less_than;
        set_range(first1, last1, first2, last2, result_a, result_b, less_than);
    }

    event exec(command_queue &queue)
    {
        if((m_a_count + m_b_count)/tile_size == 0) {
            return event();
        }

        set_arg(m_a_count_arg, uint_(m_a_count));
        set_arg(m_b_count_arg, uint_(m_b_count));

        return exec_1d(queue, 0, (m_a_count + m_b_count)/tile_size);
    }

private:
    size_t m_a_count;
    size_t m_a_count_arg;
    size_t m_b_count;
    size_t m_b_count_arg;
};

} //end detail namespace
} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_BALANCED_PATH_HPP

/* balanced_path.hpp
DtbAYwvgtI3n9HlsqRV8/4cfk31u5CFXytv3Jlimt+8dYfk9Ehz2HnqD2shq/F2W4rB1wor+4bGNjBe8H22Fl5ae+0/xd6D393Owh3wefMV413sd38JpJ4/thYM2Xsd+9AY6DtH3LR/z34l5nuc01ioWqxrUJ0sKy+3jxysjLG+3x8oLS93l+auIXPBv8lYTljU92WFnIResu+cKK6jl5eoIywnyr56wtHN87jYCm+f1XoqOf/jxmgnLDs4rWgmLBba0Q+9cP97V6OjssQx0bPR9r0NHoo9vT3zL8Db3EVZUz/M3QFj+Po8NIh7v+ZgPoW9DH98RYI9438YIK6wafP8H1t3bPAXfBnm99yAX1Nzuw75J3pbZwjJ7eWwufYO/m/sY+fKAty8Xmzd5uefIl0e93EvEKNjXLYL7eC/3hrD0gOe3se86b9+72PKG9+194rbe87IWWxZ5bAO+ZQf//h9YF6/3E/oGf0NrF3qD5+9uciPw4xv8fbaSw37Evj98/hUJy6jhc+0gvDT3vh1Fb4a35U9yfLS3OeEK+RE880qDTfBypwhLCZ77pwnLqO9jWRVsrR/vTGGZx4L6n7D0S0s57Dxhj8+o7LALheWs8rw0FJa9OclhlwjLq+Lj1lRY7u++bzrYlT4ebenb13N1lbCsNp6DLsKKDnoOutE3WK960Df4JvAm5FZ5Hf2FPTvd+3sr3Nf0coPharjnebiw1KXe39HC0oJ9+3j0fuLjMRn7xnnf7obnXSkOm4ktZ/lcyyG+nb2Oh4XFunrsUXi+zOt4StjHM72/z5IbY7yOv2Nf8M37q+Tf3Z771/GtkudgKVxVjnPYCuyr6vuuwt8qHvsQTgPsYzgIaqCbhRVM8PHYAffB70r/A7nHfI4Xwl9ln397sPl678cP+FbXx+1nuAri8Ss5WdVjR8CWeO6P41uAlWittb2Lj1uSsKJXfP4lC0tr6bFThWUFe/QqYBlexxnC8pI9VkNYypue59rCcpsE9T9hOa94rtLo28Lz0lhY+h7P3+XYvMXnUEt0tPd+tEFHA491wOaRXkdnYYVX+LW4q7DMDd6P7tiX6sfrzXgtPVf9hGV/6OVuEZbxY2mH3Y7eCn7ODAO7xOfVHcJSd/q8vxO9hz332XAV7FmnwUuwFs/AtzO93Cx0TPDxeAie53qb5+PHs56rJ8mNJd6+Z8i1a1Mc9iK83O25X0ieXuBzfPGJfPH8vSUsNtbbt5y+SZ77lfgWnIl8gG9dgvofNj/oxysgX0r78bYTj2Z+vM+QC/z9ktzo4zn9J7Y8Hfz7f8SowHPwE35M8rYcQC5Y1w4LK6jisWPoCLD4NuKqso95KWGpE32+lBOWNsbLVRCW28vLVQY7y/NyurD0pt6PVGHZLYL6n7DCX7zc+chV9lw1EJZ/vuf5Yvx4yPvWBOwpL9eC8SaXdFhrsHJlHHYlfW/yudZJWFGXZIddiy1LPXYDWLAX6AUvwXttX2EFWT6WNwvLDN79/iYsL5iXWcK6B2cno4RlBHukccJygvPGScTjYh+3u5Cb6Hmejn0DvH0P0PeX4Pd/8Td4/3gErlr6+D4Bp6l+vKeFpWz2/r6AXF5ph71C/u33472Gv8FzcAk2H0py2DLGC+zLR26L17GG/DvHx/IjciOYv5uIURvP6Tbs6+r524lvwfnRF8Syp+fga+zL8fZ9RzyC2vo+bGnp8+oXbN4U/P1feAnWgz/ARni5uLaKUbCeJgqLXeR5KSss9W3PS4qwzK0+HpWE5Q7wWHVh2bV93p8trDBYh2oKywqwutg3w+dpfWF5e7x9FyE323N6GTYf8zFqLiw/w+faFdj3d9+3vbCUwOaOwtILPVc=
*/