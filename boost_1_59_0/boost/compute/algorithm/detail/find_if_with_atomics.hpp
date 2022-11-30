//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_IF_WITH_ATOMICS_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_IF_WITH_ATOMICS_HPP

#include <iterator>

#include <boost/compute/types.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/parameter_cache.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if_with_atomics_one_vpt(InputIterator first,
                                                  InputIterator last,
                                                  UnaryPredicate predicate,
                                                  const size_t count,
                                                  command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    const context &context = queue.get_context();

    detail::meta_kernel k("find_if");
    size_t index_arg = k.add_arg<int *>(memory_object::global_memory, "index");
    atomic_min<uint_> atomic_min_uint;

    k << k.decl<const uint_>("i") << " = get_global_id(0);\n"
      << k.decl<const value_type>("value") << "="
      <<     first[k.var<const uint_>("i")] << ";\n"
      << "if(" << predicate(k.var<const value_type>("value")) << "){\n"
      << "    " << atomic_min_uint(k.var<uint_ *>("index"), k.var<uint_>("i")) << ";\n"
      << "}\n";

    kernel kernel = k.compile(context);

    scalar<uint_> index(context);
    kernel.set_arg(index_arg, index.get_buffer());

    // initialize index to the last iterator's index
    index.write(static_cast<uint_>(count), queue);
    queue.enqueue_1d_range_kernel(kernel, 0, count, 0);

    // read index and return iterator
    return first + static_cast<difference_type>(index.read(queue));
}

template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if_with_atomics_multiple_vpt(InputIterator first,
                                                       InputIterator last,
                                                       UnaryPredicate predicate,
                                                       const size_t count,
                                                       const size_t vpt,
                                                       command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    const context &context = queue.get_context();
    const device &device = queue.get_device();

    detail::meta_kernel k("find_if");
    size_t index_arg = k.add_arg<uint_ *>(memory_object::global_memory, "index");
    size_t count_arg = k.add_arg<const uint_>("count");
    size_t vpt_arg = k.add_arg<const uint_>("vpt");
    atomic_min<uint_> atomic_min_uint;

    // for GPUs reads from global memory are coalesced
    if(device.type() & device::gpu) {
        k <<
            k.decl<const uint_>("lsize") << " = get_local_size(0);\n" <<
            k.decl<uint_>("id") << " = get_local_id(0) + get_group_id(0) * lsize * vpt;\n" <<
            k.decl<const uint_>("end") << " = min(" <<
                    "id + (lsize *" << k.var<uint_>("vpt") << ")," <<
                    "count" <<
            ");\n" <<

            // checking if the index is already found
            "__local uint local_index;\n" <<
            "if(get_local_id(0) == 0){\n" <<
            "    local_index = *index;\n " <<
            "};\n" <<
            "barrier(CLK_LOCAL_MEM_FENCE);\n" <<
            "if(local_index < id){\n" <<
            "    return;\n" <<
            "}\n" <<

            "while(id < end){\n" <<
            "    " << k.decl<const value_type>("value") << " = " <<
                      first[k.var<const uint_>("id")] << ";\n"
            "    if(" << predicate(k.var<const value_type>("value")) << "){\n" <<
            "        " << atomic_min_uint(k.var<uint_ *>("index"),
                                          k.var<uint_>("id")) << ";\n" <<
            "        return;\n"
            "    }\n" <<
            "    id+=lsize;\n" <<
            "}\n";
    // for CPUs (and other devices) reads are ordered so the big cache is
    // efficiently used.
    } else {
        k <<
            k.decl<uint_>("id") << " = get_global_id(0) * " << k.var<uint_>("vpt") << ";\n" <<
            k.decl<const uint_>("end") << " = min(" <<
                    "id + " << k.var<uint_>("vpt") << "," <<
                    "count" <<
            ");\n" <<
            "while(id < end && (*index) > id){\n" <<
            "    " << k.decl<const value_type>("value") << " = " <<
                      first[k.var<const uint_>("id")] << ";\n"
            "    if(" << predicate(k.var<const value_type>("value")) << "){\n" <<
            "        " << atomic_min_uint(k.var<uint_ *>("index"),
                                          k.var<uint_>("id")) << ";\n" <<
            "        return;\n" <<
            "    }\n" <<
            "    id++;\n" <<
            "}\n";
    }

    kernel kernel = k.compile(context);

    scalar<uint_> index(context);
    kernel.set_arg(index_arg, index.get_buffer());
    kernel.set_arg(count_arg, static_cast<uint_>(count));
    kernel.set_arg(vpt_arg, static_cast<uint_>(vpt));

    // initialize index to the last iterator's index
    index.write(static_cast<uint_>(count), queue);

    const size_t global_wg_size = static_cast<size_t>(
        std::ceil(float(count) / vpt)
    );
    queue.enqueue_1d_range_kernel(kernel, 0, global_wg_size, 0);

    // read index and return iterator
    return first + static_cast<difference_type>(index.read(queue));
}

// Space complexity: O(1)
template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if_with_atomics(InputIterator first,
                                          InputIterator last,
                                          UnaryPredicate predicate,
                                          command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return last;
    }

    const device &device = queue.get_device();

    // load cached parameters
    std::string cache_key = std::string("__boost_find_if_with_atomics_")
        + type_name<value_type>();
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    // for relatively small inputs on GPUs kernel checking one value per thread
    // (work-item) is more efficient than its multiple values per thread version
    if(device.type() & device::gpu){
        const size_t one_vpt_threshold =
            parameters->get(cache_key, "one_vpt_threshold", 1048576);
        if(count <= one_vpt_threshold){
            return find_if_with_atomics_one_vpt(
                first, last, predicate, count, queue
            );
        }
    }

    // values per thread
    size_t vpt;
    if(device.type() & device::gpu){
        // get vpt parameter
        vpt = parameters->get(cache_key, "vpt", 32);
    } else {
        // for CPUs work is split equally between compute units
        const size_t max_compute_units =
            device.get_info<CL_DEVICE_MAX_COMPUTE_UNITS>();
        vpt = static_cast<size_t>(
            std::ceil(float(count) / max_compute_units)
        );
    }

    return find_if_with_atomics_multiple_vpt(
        first, last, predicate, count, vpt, queue
    );
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_IF_WITH_ATOMICS_HPP

/* find_if_with_atomics.hpp
cvSpwb33iVqJCbjP7qMYIq0Uzj/YyRZBlE5EgI9QQMmeLCByRcpBCJibxy0mb9kxDeXnhTLdDj06mxUpOCwyDLBzlXON7iYZumRPC/AHLfuQc3GQCth25lD0zoWesNqJRyZynAGMwOYsyVXS3DTnHXJpBjrEGpvv6Gh2JYpTMmJhwSLjArNHyDsnldjAynYvLhuRxaxg8WkFjLVdE+QTUajDCfYTpuPQ3RuTkU/ZvmWAHWlrWKMTrWpA6hNc5QmhW16zZxxytUhX7ubkp86/NcoPZtYc2y/jBpDFXXh4lZC63oxJXc6s2VSBsP/+MzyRV9zOb6usZMFrTKN5fOLerqdaexn4KmwqkYTwy2oZdorlWy2pdxb+JTEi9AayZJqKGpnGSdgpQH/Z1IDfGfWwe0sIKCaDlMWkojAfiydzteB3UOV1IEhl4cRFAQsWJHYCZxpEsTOVGObfh4zWVb67u6ruxE5m2CROan9KVeCpZFn8tZNqt5EB+Fd5zJiiE0jJh7pFGsfpJWujEuysqDOpc6LbtOSXi/tqFf9pVgGiH0LdgoBwZmLhse6Y0SUeJtGU1/MCZ7dzqq5mbeoNiyi7ctXvpvC/zAbEg2ZULLfCeHEFKQMMMAaxcqe40gyXrpxch491SzugmqV/zWaGnT5Pm0fjy29UNjbhLGTClHg+2WkNOVtMO3RpCF6JMM294GEJaL6xcf+RDQH0Ed5H5ywg5asyBMPkeFcDHsJYK3Y3sdQb1AVrAtL22gzszCAWqrQAqnyxP8qLGd8VGAyxEj/41REENxQrd2al61OWXORxwXp6ZRGtQyfUzq9eB6cBx4RMGo5TaPS8dcXrR9vxJJtKrHmjwnvk2OY8EplBMrjkFxg6vJJfaBisu8DJR05ej3gFmwwmpmqMTxqMTyKMT+aPS5l9IbZghamQPhefRg8b7gYuRUGQDPk0gAkqHw15Xcd1Ep5GJ7j7Ns3pg8DwJ70/n67zkywSLwvEtUJfq8DTRr5QmmsEEhFaxsbBAIrs1+Ivn0ycEqvxsmkyqjxdHCO+d1ToGZdk1uneBPsTdkXMs6Wchs2HWeljw43RgtAcPxMkSCcU496sDPJgrwP46//bdA/eqwoaRs2md56F8pjAp4SH7/4pwTg+fcd+41kSGoveDrstf0CrDq+DFMZ/VnGX0E5NKEKdDL4dNsE2xSeA449H0mmiU1zkRt+IzGD9imfqOFQI0yfPngp4jUoHhhO8YHkbEEamN43+XTeOflUBAXqYTXvC3UDWjzFjcA9kdD4rzva0aNXdMHIka8YPiTBzns15TbB5SYjsVh6sLghVbUjoYOHyDnA3shXY9Qa1y/JfM/lN9oT1ioYNTIagYeAwW21iP+WGynpkm64JKfmp7fQAdnPKX59W5uWcb1YiQ9S5LIWAwCP8mLT8DxUGXhPRCW+SHrAR7KmEU3N/Gk7Ysl594aMwcoKBJHcoURAxpWL2X4ekoey+k0cJHYWY5OW6Thj7GPxP11ESVfqqPHUReng/59R70HrTTrASvOdZeuaabRQ8ofmOeZTw9KsDS8shgh4WAwBph6F5KGpAKE+yTduh+xlmYloqknTQGvyoMhElRqfEDoBNgHBLCvgwtBg+QJF+SlD7QsXp9Zn+m1Wwif0bY2lHjpCzB6vQORImPp3PuIQwXDYT9DKSaVCNpQ7Pd66W2nHNcsezZnXu+eHK7127ATWAfveaN68Bhf3VNnIxGEKcd+DUnM770/IbXSf0BoEkygOaF9xnvkXVCCGzCKjtcF4PLZ18c/2mNMmkVsXWc/kxasWJmSIHyt2kcpPtF+M0oWf4f/FVvKgr7D2wGnzbS/41OK4xQbwO1s2FD6Xr22B3Pu1UNNxL7khvwimK4MAMoaVLweq7sKLSjojUUJyns2Rd3j43GEoG7199TiFrZDCW8P6nt/gBEPFKkMlJ6JeqdREVdXVxHjGeWtqkOxGVM8ZPNheqxqD5hUC0ram9B1JoL6MhHzG3Q99G8B6cGG5NTZuLAICM3qX3YEUM0LdgpIHb1hktU7ZR7NDoz26s8+b557ielxxEL9uIgpdDck2irEKi/4AsbrkJL5rjUIax4nA5ynOjZIS7GPT0rKX5gDd50dde+DOV7rt1ByVfe3hr6byOP7OmhRBdXj4aVG/MFnzFbTNXrNJ2qJ8THglrMsSQ6uQ+eX7UBWldZrn3Zxlw2uetejcf4HZsDN1SfST40tqfIpoxvJPnPNHt9jIbcnQ0aN+HLpsKat4fCYALdKpHNRmApMfiifuzuXF5m4T5ETEnqSgxnERI/vVl3b/dNbhLH1wKk5ILH6cPiNnmOhGSHBYBgazdVUbsig6ThD3hvy6XbygQsfh76ztjdOr+UN4PxHvvy++mjjW7zNWEm7bX509GMVl35Vw9Ln5xvuaZySSDhqZEFzAgGPvtFzNLrSuip1RvhtWVPoYHUrEomo2B0lrty6BKKY0MSom1DQGm34toWsJKcCfzlQI5dCtOj/h6kswZN7sfF6SgweXDMnGEzVO8BxGcRvNrXOpe7OevdsDY+JFO948Jbgy72X07tVAZjEoQG0h+OR17wj0WAi611u56rYv3ALow3IaAaqAg0+vyK76ARr6ANl641f10psoPn6ECTbqulYSbwDoYOTACXuPtUxF9d+tAsIIfn+nUUhyX/Z2UB10hIWPJ3A2Tbf+BdYXpltOgif31AwAA+P1N6obxRl5epu/J3CYGpr4ixApDtJaXd1aYFzHelhdKhCS33jKWQC2CfKFZ49aqVjeFr8Qqzsx71EaLNxQpRqUm56WzsZBiaVEeDCVmpgjPsKS2yGxp6j4vsaGPp0ZM++U4nbmy7Svtfd2VdD2Zyf50uGk/vcxxGrGsB1mH/H4/oI4M5vP+LuV0qlf1ucSmSn6s/Xlh0ult/rx9p23zOMvNPacGt7TzAML1cnEdaM0Dx6XwQKD6PRk8feoosVMcfsWaPYe0S1sV1Ijc8pJ37Ww6o6DhzBP5bCaPneyea0HF2a8VGlbXF44F93xf1Zw9iybLjlZy1jmVmjXViKHvjnge/Xh0swk/7uy6tXwQZ1Eqtmfhmszt3A/ElbqwvGk76XlEjQxObhfaSczgHprQ1pTpVWXKG5fYfU3dpEYlyex9mcibGcHz73/fTFr8iseDPe/vOAJsjdTyYy5qDEChamKrr/CTp3hg/Sx5HigSnDnNWA/XN5Zhp30FB4V+e4fKPY+etgT0CqlopWifwqy/EOgU1RnWfB4SupLoesqhnm/hAySKRAijjuAC8YeskgM+D4U5BcioVxPLSyD5J78dbkXPDrWiD+RkAYg7kJwmQ0XgVOUfWbRM+TEYbNcsRPRFRpez2D1NpaFvnPzK1vzlrZVy/GbQGXy+bODaoqB2vXPyL5qGMkp9Z+SjLa84NIEeWGTgsqWqkfNSXWVz1f4WtLtcedwJx2Ij1C8f0HXDi1s3ZTdhERY0o4imxSpyv5aoLHmz+UFD8926eqs4WUqzXWjWapdpfDhmGdcAiuTtFB4K3Ih92uzAWnu53hcNa16Foobz5Wp9UPP1TOu1v0t1eQXbVWuhObT2WxnN5dAScMnpev2Rw+6GbSfL4J4Vjs5Zw3UAUytSpFQ6pSlYEQawv8ulyNYodqqFHNb11Nq0et5tB2ryXyyhk/t4i4APqD9JavPLOZozQIX5TRS1BiAy0H+Stix6ISgGFeekn9sQ1rrO1e0uLwN3hrGzLXX3w5f6+SqQd65qFNoj15HN2NVTN9ZpVsMot3si/hdXN+sZ1ICYGk80MvK4cE+Ntila/ZxPe9h2THnM+g29Wu1R0bsvrrx5w/BYvdm0CbwewumniSTDw0DAPfwNOyNAEqqmclFmAb56+hC3oeox13HVHIZeBsN3GisWk1ovsj1UDkzM7o1yN7WzIavL9bweeb6wuh7qO4bYzuC7oPLm1qYPcZZGjgsrkGlJow8pA0JauLKk8ZNnr1J3mImfapRK1g9x13UsoePAvBihhGTV9EncuVGH/tEY6HWgCSvYm7XVx64t5qhelnx7PocOx54v4oBzsZU9n+k3FuEiJJGMAcmb39XPGlfw/FQMKTL0to6qgEexmXGhLgYmjc/NwZ47P2pk7WfT2OqDWf+wfjrU3603MiuK7CiCk02PG9OaUVN8oKwJLfMKgOaCVNrr8v0LOcuSETTVOt+M1HTmDh0RX8eQ/YNqYvpU55aNhxDrQZ67vroTtXdODKulA+fZqV02DQhlbsHJ2t9YhDRQrZ+Mqu99iY1Wp6aG/qutYakJNvSLZAxvvqfLWX3evymfrt+Bqj/ZEn6hBelecadbCmOrCekVKHviVl7w0w01uXx4zjVyYNemGamDQpBO5GJp10r0Ug+3KjEBgBBusgoYBvU6eABNMXxLr+sDchbP1nQDAAQs+9MISR8L30oci+jCTOUKskvegWM+cvucvezR26/LguETlNRknFw1Dp3nxOqVa61xb8JowW3uFmu60tCnQKYxAl8UBn9UJ4J9BJ3df03IQczjaEn40jdkLCyvIwHNIWE6S69uJjQMn5wGGLtZ9bddG0L95QCirjFUq7KJxc0ymAuQbWtNd947kGwU7e2m/f3dv3Yu1qgXM9PKggkFJDAEAYTijhLz2n/HZckdz1ZtTx3XUX1HTuysBUakftUme13UNW2d8QdFv4EFi08/x/OEQad0MpheyVp8DoM5Hxdew8R9V15b+Rq40yjLtgcieR3rPvFR77r2cm5p7I91bweJY6WGCFh5MwHRzuwdXveXGn2w/23UsnjkC+VfhqB7S5+1r6wQXcwZBDBJ8ZY79fN3RGUHHUzzH2Q/4hC9kzP2yMQIKLiHtg97DRBS3iRiHbIJMG9RDTCTvln2izGqa1YGoXru4ix6sPmSuIAtQR2VbGE/qGSZg1KKXDVBznq4CAfyhYsRcF6R9ldqACyDxOpLwssGt2bHFau7P73KBYiZiln8gSgwr3PCtjfteLZBVxxB0OQEoK7YfKXCTjq4o4EQDJoZIQCQHfrP6zkRDyjTbhECxuNW46rRApxfatrWUmxORlSi1DEFoKpXZPokUw976X3kvEmiV/zqxR/e++kOO+0C1lKoPUsmZgo/P3iksBYHqJ+/tkrKm2WnbM/9+Tkh53VIFkDOv1EIlzKqsrsO8/7sh2eY7iqfZ37iSIl1Y8frxfyhvwND/Pr4W7RSU5+PFVtMvT58rcs/Ux0IsTOwcQioX9nJoQKkYy0f8OerfZGz1wB/MnCrKs/CGjSuQOsHpuiMug4PPrJmyfK6R8XfqBRQuUelMQsGm9Z9vLoNADBcrt4n0JucVkqg2vTfLDZUXirJ7gOB2SCTvIKfuyr33HTvq9NZ42Eat+ExvqcOyBb+StoSCEtH9zT+CM8qNHn6tJ27gfyoqULIACYRzFzTUMQ1/zoknr+YOVIVB4H32jOpa19t/shyfd/4Gggym+MegbPVPtwARBdZgMdbCxKl9n5mCDlAV30QHPSi5nozFRJrGi2UOET6mVmpi2tU7i9af8g5wcHJa6VHjXs6ETRI+07NstSGt02Qzia+BRb2/UZg3skqbrNVrORGYYg1EiKfeuNOjxWv/Zz6u7Z7q3KlXtUy3fKFmdXzY/MHh+Y3Y3WPeCW4qmJUl2VxXJG6h/wT5JYtIrDDvS55gJWSexXKgCiECT76K5fL61HngKZH+Ssx3Xs//Aylnp4e5snknunwfz6/Atpdd3zgz/9ik1N7jDzmr/97nBSZviw7eVZOJNGwHQIKHErB4NcCKBLToN2xAV+rv4nL+53Hy1lVszCJNIJCHawudi3mDFG13X4M6ohz1AfDX4uxgmkEBQlm5OqDPeKX+CXXVYVf4hPUd8/Mj3/X1IhXZdWiylTyKrKIkUwo2lvyhn8jl1QiF+bQ0AyLaMvsUYA+w7wEd+apPq0GS4E/Ov4OCkvv/urIBZRMojFVsUWdfsVdBSL6EZqQseZDFP+1MCmp1Vb8z+fY1YQyzt0mOhNnWQXcPgUob6ZOJhCJDgClogwi1Acw1bBSfI0ft6zqH+fa2xRXiOJGKBbnAd4AvnQA8wqe9CVOHZa9y8wIMM8OEwq+k/n8d8ZGYXl3hqekUntOqX5oJKqVZWIJ7h2eUo2xHDxCauaeaYFdNciTZbXOuE18/ID6WhNhX4EOedTwco57E56HrPQNHlSUMWAF3gR7XiIrxnLaEDv8pf+3u2ZzH4C8Y955/YkGPvoHHA+px4ahjyv8f4eOXHHTrjQbkF96ka5YghxjfpTi/RJymTbykbhLBdOaT2WoNijZedZs8G6naqruMSCVhw8CQm33IjgRi2g8ecj1/Eh6Z0D4vsB2taMpR4Dmy0hncKrCI4R6PP/xl9MLwC6XGj1zdX0QltzABYt7DfT3W/YBZ0t6TiVA/e34QaYSfEl9rILJJSufmclfHW7ypfFDGf/Uo0HGltwVcUYtI/0nmL9wWao+2vE7vQHU9uV1zok8aG/WIZVJz338hv/7NZsBCxGu9UxvvN+EeHvI+12dKOyJEDThwU95LfqtSyBb+a9m5D0wIeEQagPFSoJk18kenlnRBZpKD/vAzi9hafhlHWahqMe3Ju5SPvo+FXR5cnE2DcqVhTu0dHOPookeQxMA4VXBnJCB1VBExp5rCgkh01MXFMvN0RoYoq5mDaxTBANqkzNh2kzwt63V8BWlv2dKnsO0mIFpiNeUJLKy2+xrlD+hH5JXxL3U9VOOPNEHTsLfG24dRSxyK9p9NBmSfOMFnKVZTwmc2UVcKRFI7eDyP/6aLVg1ekwt72wi7NgXfE3P57VCJ5fmPrRr1dqotWeX4bpAA8LzPqJvoo6cMRsKAZ7lg0jJiWUDcpg+xUat8nVEfAS8ESl9Nd8xyRRLksdmsVTL2BkDKrTPXwhn0y03MBdrjYFV1SzZi0r9a4tzu69keTOiYJnHuEKcU8E23mgoWMbaRgeK/5bJfFhgWciGvPKlel5EDS14upxBIPjgR9//W1DUtzTrFXtyIJ0fracj8nnCU6iRlDq1PxVVNq3O20xKJUx5KG8h2FbDUl7uwKemplsDWSJvB3JFdxT45YAP5HybKkd7StEGLcOxIliv6FKmgrrp+C30XlViIdKUqVV1kqzc/yv2X4gptkvuJgVcYyQhBLOiOlh/1ardDsDlQXM7cuyqS27/L9NLauEi81fzqgh/ygXgQx28pVbeYOEtYXz0T+JdR4n0PS1bNQA9KaGsXpa0gNoqzrNf/vp6r//SI4+yvJNYgXn6iJob2vua3M3hjcN6eoEBk6Sjsc1JuGhcl0a57MWq1efLqCJFKj/nduKbVuTgWz9thgz+W4DDyrwsjfY8iVIfvAK5k/LloVY5QNUWdWF1Vmz9wuoLWyntTEOs55ep8Q5pAlizUpDCqJgqegbmXWKpFvV2v7Tzh8MDhvNz7rmdVzQLWoSFeDszNBOC1SlSve4JEWi6N79wjaP6HqwzJ3vbmDSYdzSfj9kvIMDSl5JsRqy3p+CEJE4GGS4+zYsmqbPcj1STsYFVi1SBilTZbP6eLUu22WwO8m0dPd7mT3ezmu/23IFYMPZoLR2aWerOccG3HZezukDtObbMNAnW20Ht7shgC7u8nqdospjC4QB7SWns
*/