//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_END_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_END_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/detail/search_all.hpp>
#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Helper function for find_end
///
/// Basically a copy of find_if which returns last occurrence
/// instead of first occurrence
///
template<class InputIterator, class UnaryPredicate>
inline InputIterator find_end_helper(InputIterator first,
                                     InputIterator last,
                                     UnaryPredicate predicate,
                                     command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return last;
    }

    const context &context = queue.get_context();

    detail::meta_kernel k("find_end");
    size_t index_arg = k.add_arg<int *>(memory_object::global_memory, "index");
    atomic_max<int_> atomic_max_int;

    k << k.decl<const int_>("i") << " = get_global_id(0);\n"
      << k.decl<const value_type>("value") << "="
      <<     first[k.var<const int_>("i")] << ";\n"
      << "if(" << predicate(k.var<const value_type>("value")) << "){\n"
      << "    " << atomic_max_int(k.var<int_ *>("index"), k.var<int_>("i")) << ";\n"
      << "}\n";

    kernel kernel = k.compile(context);

    scalar<int_> index(context);
    kernel.set_arg(index_arg, index.get_buffer());

    index.write(static_cast<int_>(-1), queue);

    queue.enqueue_1d_range_kernel(kernel, 0, count, 0);

    int result = static_cast<int>(index.read(queue));

    if(result == -1){
        return last;
    }
    else {
        return first + static_cast<difference_type>(result);
    }
}

} // end detail namespace

///
/// \brief Substring matching algorithm
///
/// Searches for the last match of the pattern [p_first, p_last)
/// in text [t_first, t_last).
/// \return Iterator pointing to beginning of last occurence
///
/// \param t_first Iterator pointing to start of text
/// \param t_last Iterator pointing to end of text
/// \param p_first Iterator pointing to start of pattern
/// \param p_last Iterator pointing to end of pattern
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(n)
///
template<class TextIterator, class PatternIterator>
inline TextIterator find_end(TextIterator t_first,
                             TextIterator t_last,
                             PatternIterator p_first,
                             PatternIterator p_last,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<TextIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<PatternIterator>::value);

    const context &context = queue.get_context();

    // there is no need to check if pattern starts at last n - 1 indices
    vector<uint_> matching_indices(
        detail::iterator_range_size(t_first, t_last)
            + 1 - detail::iterator_range_size(p_first, p_last),
        context
    );

    detail::search_kernel<PatternIterator,
                          TextIterator,
                          vector<uint_>::iterator> kernel;

    kernel.set_range(p_first, p_last, t_first, t_last, matching_indices.begin());
    kernel.exec(queue);

    using boost::compute::_1;

    vector<uint_>::iterator index =
        detail::find_end_helper(
            matching_indices.begin(),
            matching_indices.end(),
            _1 == 1,
            queue
        );

    // pattern was not found
    if(index == matching_indices.end())
        return t_last;

    return t_first + detail::iterator_range_size(matching_indices.begin(), index);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_END_HPP

/* find_end.hpp
tALMaZPWMRRy9B7/coCABN7YyDOJKM5i2Xo+XNeLTPnhIlv+/PJUJX/WTw+IDTIL3aHyzP3D0tsH66eHxkZQI8pHB4enQzgtD8+glO+ktY8zC/+p954buyB87q1PHf9Wf/vnM/SGHNpsO8vTKW1IbuSE6Rz4g8PbhTKSNCWLJhOZzK0utIIdRYFO/4pbQOV9noPTa/knXUnBt2MIu3ZQvM/e6tM/7+b4zQy3zd7qBeONwvFiWg6C10UGEa9hPQrXdfpwEL8Yl8SxhozCcqGjvlLicAS86eVfxoCpkK+dthzjt/qioIPULWtrmWypxWgZta/yL/I3pVYHYUc8d/vR0cYpK2F7AjuFOSvoybJX41lUF+epnImIOt+KaRPEemAGwLniGo7hOm2CXv8O2zcxgMZYMSLMZtaPIgByD0OTu6OA3HxoAsKYXwMBy7y5KHHKBLGcyxoShgYG6dn+n4019sMGCKIhWDffohruwALFXUac5k/5DE1Gamoy/iSZ14ivzcLMRACxYfLQPMZR5nBG1qPYhuYmEK+TksIui+qcPoHhp19HsVZo8lzHmpESz80siSdO1e9d4Gov4jDoVQuo8BJlrRXoNQoXzItcKQonKAcyBqq+bqOFqHoMv4Bot7RAUi92IrQCtE/FOa+/O5jwcsnoYxSNeg7CuWID7Ei/D0vJZ+rg8tqzYU6yYUEKmyH8QEKm/1OSTO2+cyd5Y+ixNDpjlzaCAmxPXdrY61HunppP3DDTSDeKvGhskzujmObpBi96WCwf3N1l3ZowlvnUShjLzN59hrEMq/UvYbQHGgstDRy4DHzcZWXvFOlWMN3IcOsNXqSKfpUwZ6NSZ9Bid0pNOavU5CHD6jUfyiyNL4SJtHJLxBrMgAJeGkj/2QMDwsIBTVaUWgJ8dR7A6FpdSUhLE/uCpR0UOuZZDbkZa8XxTZSHPhYSIn0FSLOzLNlbB2cBX2b5pdR0sYUjge5J0jgkrDwDe6uGmg9mOZDPs/Z49hmzmumJKPVlj/DsDzy2ExEi/DYsFR+bRrDD3MyrJMq5iJIxNy9QwgCATYlJGBLlkjOGg5HCWedHPAAh9unRMUpJAlh7kRywPIlRGF0CJ6KnsEbyYlnRVPMpXiba2ECBtxLC0d8zQYMPL0sAn7WLvbCePkV8VWw8HbFaZrZGhFZWtnaSTf0qPIaWJTTafdOSPLQAlgSSVcvyfO3WuqxJa9/KBCbU47f3IP7pSRPIG71id0jur0Wop9HCXW65AKFbRjtWiJKMhfy/C9+/fPn5ExbApSj/3+8/AQkhm7uMdYUz61MK6Zj6yWWsmg6miVrMSu4HhtYZeJdYhKtuzZvli3izG9tTPI1ip8GviQJMEftFLabAnJuVXeDzeAJvVw6s2fUrCD5TRKPYipEsM4OtKof0dCqbRPG+/Ner2aO+VY441mUhhZbG3rhWKJ+DSLTKU990QSRRAzdo9ifN3cWTVBxojKQC2rvdWxLXMghYrwXqUAvl9T/eoEyD5OdfdQEkYOJl3sQ+quJ1EumRGbasRT65v+IU/kJM+ZBX3sqovcmQLzUNFcMDSyHTjw0WxhEPU1hIIGs/TPBvOWdaOIuDvHSblVSr1atrzfR/i0e/r80rYs2M99WarTXn7groGEP/s43Zm7fYIVUkcWd5OupcnBFfgTNPeZRFsCLkD7DyVXL4pXdBaMf20ffE7Zu4lHjAWngCFDUVctA0o3CqKJyKbM8hW63yMX8Mq7SOfcyJjy8Ngf73hoxgp6eJo9O2mRz39ghYN03ZuoaKEEGmKoItqiklT+uqGkT90BtO5mkdlZlJEd9T7bycB22L9Lfbgodc1B0OscydWAFp2tFzQGBc/gEPrGPDi9dVPympsSp+FuCb2NWiljs6up5W8+sVkB/Q7iXAS0n3Q6esaSpd5Z7b9ekZll6HAaZp3S4/3J9MtFDp4ZTb7Qouo/KvtMsfp8rHsZlWLy+a53JNM+/wpNilHpg3V2xnWkTqZ5ZnF3YVFRawC8t1Ckuj9uJYKliQMPUf6jR1rx2kiZbp9vZueVm84GLaa+DsOedk3nNcdnFpzaGKfwvwTexesUxN+Rq9ig6ukYiD7IdZdCobb9NhHlpoRE/S42jyY8D2FagiKl+bK5a9o0TBqWJZfPdjrD3t5DxGCZe/3ddlexvo93oRT8Tu6Bjq6EV2R8+1ZwVDdg8Nmd2zwxj42/Y5/VHH+bfYkvy9FjsHRsYoYmC9Sw0TUNHkN8dhzgUr2uP7xuxovzj+wmT7uwiR4GlN07xqRflUOI/IvCQfW2T4Gng4L81GIv0lQLC65HSVfQi9RlfieSuSssLesCfvDe7hhJqeiisCfB27BEO4zJnNtPVKJRqaWajeVzYrs2y54P1Eb5NWRS4N1mR7sCZa0QxnYQACLP3TpNOQKdAuRP2YDQWhM3jvYVnA3RH0ZrccFi+YnWdL/asbEOOFN1ri+paCArUru+R7vhdUwy2e75T/icos78wjkj0pHrzaA+ULe+PrW8wBhhG8qdKiF4snMmFAsr9qVM2uipLAu7FbRG1GKvaR5XmziyKBKXQ8fJ5YJeOpLZfbbbk43pYS+eVChXvptKYl/hHIS/vWnDyM46i0u+zSbse4JQrc8MvEujuIDGhm1ZWU4aoAX8cucxpaTw2lvMG0kPVLn0yN8K6BJJX7nTase+/7v+4JVN4kuwGXx7ci5S37kOpS/LtutrvkVd/1jPf6ditsoVy4197wwCmn/LFU/q12+cVJvfu3hYnetcZ7h8HNtns3RvXOmkgbo/WgT175YKJbLXY75N49Z2+vGNPxdpVZie/49BkTdBC92S5X7Pne9Y0lN88upOzMJbcgvuTiLb9Ubbnc8nH2vDjpV8FAx2n6x9jG7SWZHq+7GMRESe6h0rK8p7j+O2ljXBDg69jdYinXn7FG/AWnnXhgqn6nz2VOswKd0YH0NQV6qzzG9T76uvMCx2OTxCN8Ds4ICe96OgTFrJPm1BRERgpovsXDClSplc/mwv2YQQ3ZCUsnOnwP3Hvt/jdUXGbTCheJ36j6H9HvnOrS78x35as3lZ/ov8M579p+VKPcZ9PVTD8w+VAKa7G4ugxGhWUOMRyVurbHq99HRMWOzO/BG/dXj3a7nHDQK1jwQIUFdvirJ0Km9b7Fru6QH+dt4OO3Dukhi/gdCAT1zHyc7S0UzbM+oEkYZtFhvyDBYg7K047EPApDp1Blq3yTKAL4zYAqyYsd8Vc38kWbvxpijwBl0CBxoM1mNzGZaCtL+qhLOxYkeBaiK/bkpfpNtg5OTh491P6gHPhulxXQ2qr+hV+57FeR26gUs2pBQrXmI3IlrzBSNaVPuuin7TmiIEuXRMF0xFBTNhCo3e3DxE3jhdalN6YEGqsGE3kWojzDKNeMyfOIEGM6bM8xTzIgr2SfZ8U/M51b01DlEyOoNMpkv666xP4acqCxLWM+2GfWYjjmbmcr2Q0/x6XM3ZUgKfugfh/UN8crai8rLWsflNQhmn/FgZ25CiKfCCauiiqmKyorVhgnEanSX5UqcErVkjisa/s3zOrslRfcxu+/oMuM26B2pouB1ND2Zvnrnf/rPWT6A9+7hxTt/ME95IxCbDLsoQcSu98n9mbgQSHhO+ovBgPz6XlsrJ9rwRVqi6GtMWIb9d4BCAk+OFKk92ZFCvTesYuu1nvHP3RVk7ZWoa09b8ReNWKvGLEXTW0tw6WflPfAgir2YvRK5SmxVr70JgRNR/8AK9RU6LSbIp22yeJkNwuvjpr43vZKCf2Utj7QFJ0PSr6eivHXnXaxm+QNAe3F2FQRfJ7VZgrDpgK6KPPBJLiSxOwNEVp9PpVB2Sobjr4JOn7OxqPwV5MDm7roE65fukNJRBo4b4OTV0S3EOF0aOkOxZa38du2UEGf1w0wY8oHaMd6fUcWa56RbO26kBVds052no+ObKQm6O+Mp8Zcq/eejlzOZp6Is+7Xe1Oil4rgFhkEDupomDsOgfuPf812eFfNmExLlN4eOMnFOAM5p/6UJWIbRXQ9zK2ggYRBkb/6OTZo36KEZIHdkdQS+clFNM7HIqNYj2fMXWjMXWCtgi1yQnIk+uf2FCLa90ML7VdsgMWvdsji0QnXNL1jQh8QfZ8jIzFizYkt9m3sNdMm6BU+FwBzUdZYZbHV70KtBSEmW1g5W30zAmq00ArgkOjsnjUshG0ixxFGRJvFMN6aW+1bQ2uBXCw/p3ysl9nUYkSl3c1RaeFP3kVbUHaw1UZg0Xu9MU/YOxu2B0naMV3r9KhSxLDwWGaxnELQHl5ROXGO8aKvPMlhBPqcMWlKahtCVN6DYhj7+Mf2WY9O5OWcpzVHB+RpLcqxnpZnaWKQnnA5MjhRMGEdYHuG8PpVHXX6F20tpab933rH5pZdNFbw+tgpdnDa/d9mM9BcsAPaxi7iUfWG0waNAz3dZwR7zWiH6OUQyX764Pob07zGNJ8xLU00xcfh3H96bJxq4LcW8vxGFuv1cIq1yiLnylnwCZ8+QfRmv8nPhq99GdLMytvw8E0syZ5lLNyNjFasaz5b0MQDi1AyOjxSwi45v4tNg4Zd0ZecPhsJet5cojDD3vq3sXNtzoz7pE+AXLEWm1wubAF8vHNUTaqx/Mu/wem5VZ3MX6BW3h3ZuBThUuz6ZnidTXJ3nNDi7Bs4O+795sucHQTX92Znomu3WZeeyl6f/eVLG0/ZVg50myovrz5Bt5B50W0/eT7ftqlbr/zrl3CT3+OxPUZH7EZeSF3ZAMZsgn4c0lo206vC7fSJbE2y8Je0OUzP0Y+myxNjjlmyMhOKhgveTpyJtGqJGf4azPCzfFxMLiOaryzAN2BC+NCZvAZHBodLmJynnVw8OHFLa79Apa7cMQ9o4DtySk2tKyTX/JHDv+KQN6f6+jOJJ19sTNCatIGpiFN2zUHUPMuuORivWd8GatMVHavHTlrRwcrV+Tq2WD4JwJD+jMxkhcaCpHWasmmeLaNQpKWc0JjEeDjssliGQTNXdrBlRIVbMaHLZtrC7pV8wc/7pETEiOgVKp2diB+Nchhq2zP6J19ZbLe57Ctb1XImHy3nS7Y5ujjuFu75ilnpoUmxm6i4GRm2+15aPHYlEh/4Jyf2I126UkjMyGz36DuteFU2j5k31xf5hajlz26J+uz6GXN97SVlYbe0OmGySLdJvNIEm14YGyc64AeUYHJb59UciqTJ+0u8rnaffH9bl0W1GrX41G3WzJGx/+vJJPznDWfJ2PuEChEHsYEymR5rS2yPQ8GCs1Q8gjAYk/5hMXv3Op2SxDwL/nyr/8HWAqwQ4h4C6TR45BVPhI6YI+w6IVi2nY6sN1MRBgsJwX0fiYTzBIqP3gkEMx6EAhqEWwJ8HZtmE+wT63MblAyuDSiXWqehdSVJ8VJBdvIYcbbKt/SbMiyda7WOfgY65+WtxJ0U+rJT8woyaM5uygzcNNZfvSOugTEKMkTB2HW61kF8SJdX7DYKMmUn25ljtze0I0qyufj6eL/rHsJpuqvihQDfx552mIvlYhU+mxunNOUreWVoqkpSuf9oAVa03uxRGJXj2LYBksxs9ouSjkhxt/z712xVVsNeT48hQ+AbZcANvgaWbnTPtoJC7ONqXyOibIFNGd8tNqu2LLsx8E1sImJF+VccP83AtAEuzW+CuNMrX/NCdsM4nTcUWpq029zuV50QRVNvDLwb804xiqbidWADZ64rY/tIuZda2X53rpX7gb7Xmpb3mM25fuBf/mvYEj2m9vcqdh5Qq3mVWIpys6dMLQo0VXrFN6L3epWuciexr5c43NqNiTze9Vb+VDUq+zv5u6tD4AemD/LtQaN3476g/iAo1ny1GCldKYfYCX2Pqs0mSkc5yp6zY1yd6+iRCrJ+UI9S94WiScJj6z/H0XfpUBuxV/G7rYkPCV5s8tyCOHSkQoJsZaNIOD6BvG4xtOYmbZ8KwK5azA63gNhu+75GO6RwotH5LKfnwJq61paia0c8+n0yRb+vw6vMee0I7vtk7CB9EEG2SZXTmrssmxrMhYmH+g7HB45X3q+mI/YLNRWI7GVDo4emOhxyS16shU7cYGuZPP0hUQyURmCzZvwvl8okGOTGfqDI5312V+XoPDodHxiiEOytv8QPKUDJQb1x0CzMCZk35cgxVx3DN2wU+ERhmlGQpkDlmLzwrzzMRACj4vNkERdgPpylyFWfedNE4TZLJ86wNfiFo42C0aIw3ShIV/oYQ2n+dFABIUUMyDuriBDQQSaEbBu6ED1RwnnQA/LueUQL1O7hLOrJL2gJOp03n8Bfu0ZnAMwn8HeG8TSoevXKeJpdCmvHpqIZ+BW141PBwRo6/t6u1CQn4b8e4M7G7hd16oBeyoQArBReeQc0GvFwtCsiDkGwd2ljPbdjaRP+ltk9Tzy3TRWsaK8pQO1AcPjePDjfE0F9UtVUuewoO1//y5vgTF31Q6cBlvoctgCZNgG4oqwIF2uw7UMxp/+PW7533ym2h2WsjsLRLlcOojSOU5f5inTJN6dnwHhCnz56YHk1UYntF5Tf8UJGenumzbFAwTI6hbJSwvIIVKyP59Ds08uGHHDuI+lObwKAeFp5kcxIDzUVZl4MbubZ37C5CKRpIXN6mvznlYAA5WDtD57LvgTym3NYg0b9ufca6s8g9Ocg89rE6Parh5WuWm9Uh7xwJlus+GT3hVRQQY4o6iKmumZX1U/pmJoZ+HZx6F59csUl0aywuwyZxo3tQbJARVdssP8NbwXn/dUjTt5pgW8rdzgrMkxjFsqAC0TLj6iq285Rfo5lrv5LZE/mMQbVaruSmlg+2Ms2cJ15r0GtEB1KxB5bE8tt1x0DdFz7FBhl5OfoMj0kb7qIhqAB0Qg7w5eYwU64m/39Lvrco536js5SmU3v6bC/ldIQL9pf3v4j9r84NFj5zvjqr8U0d6Vx2IKEyinXMguzQsZW/l6qvEaVr6kwjc+3qtFGVbpRlenYzvmYqDL4a5SPMzOcKYKjASEbeD+SZtQinKZRdzOcr4JZ0DS/T2+a6E0dTI2VobHQaJ/NMNR3UYcvIdC0KLOsTH2dITn8xRMg4FKNrYlvxknBH6089oKTAu/ilqGDlPb+8JyOds/hWR2HtY5Pjipouev0WGZ69Ed6bHR6dBg9V1UVFx8ePVb+dsEJOl2ysvB6bJb9GvWo1w/T6zJzek54oLFovvzDPBrtlsBfK0vNAjfxhD5aijly2L30FPyBGFIWQmyGGRkg2m0DpY9GHrNKAJGDpGvu7rJw4RhQj788vor/SOn0OubsjNexjRhsjNvEyGI8HVvrMUNbWU2dSrP4dlacN7tgUB/ejGjPqiyjaqxRNd6omiAnFXdzrXLABccsaiekR/MPgf+JczgjW61k/sdHt028BbJH99Z9XHMr/7bwL8iFplpsMDAyMbYe4aed/NvBv9hokviv8548kcydnUO3TbXg3VjCtRVsnrE1i39H8y/4u9xdQJAvy/1gRhn9Y/cTn7zqFAdO8AxSsXcYK+b8gQBupBxyxitnY8XA6Fl+ODAZK2bGZYzNqL8ETG5amivYsKmrmA2b2ISrvliZcJWFU/5CVNFiKu43AP41frOQfm8Le+bl9hQabzawXdZrbEzyGtyyjaXV/Hs3/5bz7yr+Xc2/lfy7hH8jXB4CZhhLwRTZxkzCzRyV+Rqbfl2HDfgSFyJfaz7juiT1oc21vDvrlHU2K6RMp2wV7nl5tWhVZHhe4cKo7UfzaLWSCtqckG3pJepWMf0bOY91cPFbx4Bff2kVE2Z1q/smW31mMjygDtU3F5+B2rJgCJ1p0yPAweWhomtj6XJ1AVoCi9+shUgdJ8IDY7qTELj0awFOzSGjcsQtEWnOwqEUGQtkrqZlS1w2ZBXYNxZ8FoFkeBnPXXPnMUgOvOfDCMv4SxvLJST/0r/bxjotEee9+nFmOsvMeWFEri9LwjT7TX/4KJ0cR8fW799Sxqg1VuR8Ykj/8xyOfDRM38ZRsiMDm/qhIDRmnmKvc8eftuYaXHxfdi407nScnXt/3VnsXOhMpQviSYtYmqGtz5t7d8QnarHE2lMF29mJwdgLD0q1FxralsDuiPdgQ3vKwcaWT7AbTomeh0eHD8I0/pPgFttc/jmv10Wp2+nF4RbG6HjIZw1fQlSliDWIpoup6CW/6lek7zydH3FPE9MnUCEX07a2MSTDAPLO9+oNqYyEAsFZSszDUIsNingDoTR5mvEsVnje3PLoPdTw6Hwg65rBjWxQs1BoGwPbo/3y5tRHRoq6LWxYWuSuRY5ArH6xR8TqBRtCBrZXjTojgWDTykDvYmCdBbd46vAQ4E5bhLbe8CE+d4VXEfabPvEkWdElOzQ4BjFiGEK3WY92QAP18EKXKFhAFDyRLQULeNkzd3INjBH1uxZQirtd5k2Z4msztpMtuR5rRqJvlJG4EWwzZsl1NEcb7DnawHN0bZ85irbSGjpjji7CI2eOWu05+i6FFkWwjVg90akmShRkZe8w3EaKfPInYEFKwE3Rqs9hzp0/XBhCErMUvVdEpRA8IfoWRzjKDoHrQklGdkLHlvTmWB9iU7qjnintAyFD7/fmJT7WcNkebGx7b4oVlHYdG9DABQJwCvKcPg2BH4uItZnRnexP30JzsU7EpBmtVwG6jYIFmJbzD/aRAY/va78XI8ZLf7jcZcSO+GvG8bwgIuJ5bm4RraEWeI3QGgq2mA9milSONk1rKdgame1IurUOD3fbs5NjO/Rma51GsCtba41DiYds00J2WBeeRDfXAd2DexiqBBps7AhVoG/GYiSG+UkwPg/fQe0xeXnoQWk5S+Rc6ZrELnNXYyze4Q3tfas0h4OecGu0NpZKdyjvt47/y+ivM2/yFhMTdIRxjbaw+4m04NAtHXc/h53d9vEPDq84SKRMkoltQIhVLLxIihFb8RHRN09jOw986q++FPaSD2b5q9lEnvjzW+n10WHwFTQ3NLviFpbo2Gbcs7ml1VQwmUVGm1G8ikMtNkTc6otaundJujvfWsUghsNKoaTgkOcGr2Goaf8LKdmHpyzsLr/VDqt7QC3ysrLygPNE3+kO2U/LtXiy3fLuW07BfepJPxFcQpXqBD7wht2hcA7OgwPWhhXso4AEchNxvaaOLrDRpTV8nzLPHanKZ7HBejvuLMQ5Tvc7lIE=
*/