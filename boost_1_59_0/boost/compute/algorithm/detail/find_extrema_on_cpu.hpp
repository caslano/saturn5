//---------------------------------------------------------------------------//
// Copyright (c) 2016 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_ON_CPU_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_ON_CPU_HPP

#include <algorithm>

#include <boost/compute/algorithm/detail/find_extrema_with_reduce.hpp>
#include <boost/compute/algorithm/detail/find_extrema_with_atomics.hpp>
#include <boost/compute/algorithm/detail/serial_find_extrema.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Compare>
inline InputIterator find_extrema_on_cpu(InputIterator first,
                                         InputIterator last,
                                         Compare compare,
                                         const bool find_minimum,
                                         command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type input_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;
    size_t count = iterator_range_size(first, last);

    const device &device = queue.get_device();
    const uint_ compute_units = queue.get_device().compute_units();

    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);
    std::string cache_key =
        "__boost_find_extrema_cpu_"
            + boost::lexical_cast<std::string>(sizeof(input_type));

    // for inputs smaller than serial_find_extrema_threshold
    // serial_find_extrema algorithm is used
    uint_ serial_find_extrema_threshold = parameters->get(
        cache_key,
        "serial_find_extrema_threshold",
        16384 * sizeof(input_type)
    );
    serial_find_extrema_threshold =
        (std::max)(serial_find_extrema_threshold, uint_(2 * compute_units));

    const context &context = queue.get_context();
    if(count < serial_find_extrema_threshold) {
        return serial_find_extrema(first, last, compare, find_minimum, queue);
    }

    meta_kernel k("find_extrema_on_cpu");
    buffer output(context, sizeof(input_type) * compute_units);
    buffer output_idx(
        context, sizeof(uint_) * compute_units,
        buffer::read_write | buffer::alloc_host_ptr
    );

    size_t count_arg = k.add_arg<uint_>("count");
    size_t output_arg =
        k.add_arg<input_type *>(memory_object::global_memory, "output");
    size_t output_idx_arg =
        k.add_arg<uint_ *>(memory_object::global_memory, "output_idx");

    k <<
        "uint block = " <<
            "(uint)ceil(((float)count)/get_global_size(0));\n" <<
        "uint index = get_global_id(0) * block;\n" <<
        "uint end = min(count, index + block);\n" <<

        "uint value_index = index;\n" <<
        k.decl<input_type>("value") << " = " << first[k.var<uint_>("index")] << ";\n" <<

        "index++;\n" <<
        "while(index < end){\n" <<
            k.decl<input_type>("candidate") <<
                " = " << first[k.var<uint_>("index")] << ";\n" <<
        "#ifndef BOOST_COMPUTE_FIND_MAXIMUM\n" <<
            "bool compare = " << compare(k.var<input_type>("candidate"),
                                         k.var<input_type>("value")) << ";\n" <<
        "#else\n" <<
            "bool compare = " << compare(k.var<input_type>("value"),
                                         k.var<input_type>("candidate")) << ";\n" <<
        "#endif\n" <<
            "value = compare ? candidate : value;\n" <<
            "value_index = compare ? index : value_index;\n" <<
            "index++;\n" <<
        "}\n" <<
        "output[get_global_id(0)] = value;\n" <<
        "output_idx[get_global_id(0)] = value_index;\n";

    size_t global_work_size = compute_units;
    std::string options;
    if(!find_minimum){
        options = "-DBOOST_COMPUTE_FIND_MAXIMUM";
    }
    kernel kernel = k.compile(context, options);

    kernel.set_arg(count_arg, static_cast<uint_>(count));
    kernel.set_arg(output_arg, output);
    kernel.set_arg(output_idx_arg, output_idx);
    queue.enqueue_1d_range_kernel(kernel, 0, global_work_size, 0);
    
    buffer_iterator<input_type> result = serial_find_extrema(
        make_buffer_iterator<input_type>(output),
        make_buffer_iterator<input_type>(output, global_work_size),
        compare,
        find_minimum,
        queue
    );

    uint_* output_idx_host_ptr =
        static_cast<uint_*>(
            queue.enqueue_map_buffer(
                output_idx, command_queue::map_read,
                0, global_work_size * sizeof(uint_)
            )
        );

    difference_type extremum_idx =
        static_cast<difference_type>(*(output_idx_host_ptr + result.get_index()));
    return first + extremum_idx;
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_ON_CPU_HPP

/* find_extrema_on_cpu.hpp
k/HR4UXM8fIclYryM2r1TZuGFk2JhmoaHktP+XjJzoUyGAIcKwcKDVGZ2YijKkaKJ/O3H6ENzS5LXwdc93kEddJzRAOJa4+w4XYoFixP6SQfiPFvR/DpO51jKOvJWUrLko2L+qkFU71QsTeYWE3dq6WsMGB3VBpOTMDRa0oUfJ8wcav510/bctE94jSWNO4WgI+3MktSzRfJD255ERo5PWo01w1SXmj892AX4B8QGxF3ma+m7zDhDw9xDwqN3hdzD1LTD1APaOZP35f5j3VW8lVaiQqspOvkSHj8d3HewN1j8i+y4LfDeocEBGSZpQfvexoCJrZK9Ito9K6J2WBLgmBaCEZlufdWWl8xGt2i9F6Qb+HgE0BfKYh1vLliXJyvHogXijiL8Y+OxZifBs/8ISXY5vGai+PqvBc2MLvgzBFiNtgQ5j9IBev6lH41IEJ27kqmtmDlg8Hw95zBfPfytQhYt+uhQUojEYECXooSvM2KbYABIRzmyL0PTR4j8OwAkkva2xKzka4+geuTzjFJr23cMT3kbdEJ2MYfaW7M2XtLguBL/ZByflovZUGDOstvFCwud5TvYC70Yj2yOF0aHmuNjJsqPtlBqhROmn0gmOd9ZaOAivjlTcTQoB/9L1cfVJh54Cq+kZUfZHcbpxUjU0i5b11MX+20y9Q+QzFi16wvTwRT5oNJDxZme6IRJ8OrkXrNkXRqewfdatyLFve6KJ8WhR2F/ZLVuQY34N0YIviWpWA/A5Vm98LzWvsb/82vweUCWyhxgEIkozzzHm3jZSTpaexn73RegMvRjz6RMZez0P3XG+pSjpLW1o3L90jT7Flc5k20VC/Itc7HazXFTKD5C9GRD1yu+oGCa8omqBST8SZR8XyOKY+Fx9//wKj1YZkD28rNUpqqGg9IFEJj0QIkAR43DS9XfWu9i9OLEroXHtT38KiAQXEmC0oWtnhXBRfnRtMcJ9upDGaHsKBaLN80HXWpkKlfFj3iOm3UGRoAiCk1zSTsjH+eV2nD6B52nAikYdvzCUtQqkkUkgBHajEqhDZHDIp/Lt9iH/XwVHPf1YZUJuMAqhSVzRVHreWh4T6n/7OSFw1H3a3vDKqgxOAAgXOSd9nG2CJ2RSQr8mtmX8CtjdO1jHJerHBL/3xbyvqI/B17fs/6eO9wyXCiggaZzvkFe1npUrspXe8xwD0W8eJ3zf/JyolAX9XklWz7yDUSCAj6aeNDMlNWvkdNA/WCudMzh9Q+Ma4OqyTrmTyjAtWjTIAIMzumsrEuwP9P7Yqg80dncKii2WdqVyFpjY3VqmddXFJhwbW+C4pmgdWx6F6IpZPZpLTkaq7YZi6vBPrOSpMBqolFXpMSNnUxaUX4DTxiGdzf6MIjk9G8DJzUEEQ0MWbiMKCgpl+hkUiSs9eMr81tsK0Vo7q7kHCqKzq1kxaj/nK5f/NI4YQa2k3Ec4iVfdSX8j9mbM6LCl/SZULxWpDWXanhWkEvuAleuWFHjyjV+q2CbUUnIrzkZ2XlvcmIotQkH4xSp41zsaCHLR7A2cEqxtPfvC+i2Qjr91Bpjows4rn891dGP7KNU/0QBKDS7ogqbUSX7uIrlKZxxYyfA9z3fe1C2jhLhKU4preYiMP3hkfg/oCFB4PK+0o2rXNpcPQagNDi+FDSGD5mNiWO+6AUuRZ9WTLNYOSQ9gX/Klyd5XcKobbKO4mjmgwvf8NJW6QtF+SJdvJ8cH8AfyEpQAD/X7/Ifc36jTmmCHUgJAH0fv5wRva7LvNv+EZxTgTxg63/PgaUWtUs9VT6imRrnReKDzE9rIvDY1jImO7eXH8ygb6sBxX2Jul64NSEPsvQZP5N5oHAFgldcW5jaSVsRdD19aLZmbyiaAkACBZOq25UqzaE0IssuMk4eHSCya0AIyRb4OakEQqmi24XIHO2K8LgAAzdtUkLZ30jsLSzdzgcVeufPAGwCuxq26uI2ZQMtQxVDfmKIjlqtjQGc4Qrie4HVK5xus+rdOMl1kMxaGOAQdAhNdfrC0JSs4jsTciBBwjB6h+tJgUOBlHg//58UiT5KaQIjjpDqImcMyfB3tuoYUdz57zD3blVjk+67T9vvo2Xq/oeCChjMWlA5SoTvBhnlF7sPN+6anlwiJLj9l5I6qn9nNXu9Tr/cN3IWU9wLRlOvt+wt55k5r2TVvRgCz1yMOcqPZpY9kSleLPZqN6ZWPVQT7ONf724hj9GoACvVxEfSi4Dq6OpWWkq1kkyZebg8D1qwJitJY1bkk+qVkXJD9pmSpspn2TT7vm9g4agBooy5KAuRoz2LooxRLU/otJqdPEtcrfZerZsnCY9LvfsP2Rb7qaV2ip8MuZi1r7oEMUqfDbcPR6uUhYGqQ2LgjQaWfTf1y/t1b3Xdy6rErGmS2A8be+VcbEGwLLjRFceYNTI6Ct3SXlZ1jZEOBeVzz8Nj3cyMJxVocmCcRfJCHGzV8eb0fcy5U2Po774PZxfSjumpJzLyZYM130UJbcQOpiLNk0ppQmcJg0anyvqWbPbwPEs7ZrVcSCtKbPuBgTMLoS/+FYvtC/9jJJsfEGfse+po/NFY7KFLRjchVlsUXw0xodnF8Dc4A33stlbnZy2MWupA8qK5G8lkB7inyi3IC+Uxt8dAo/rScbEgPnJOqRMzgH4vZImiAejSAg9Zt6id0nh1rH6TBwQb2w1YZsjVZv5mg+lwjX/0nquwH3bj+W/QKD9QgFY2fjwcBMy5OmLAAsBigAAAP0B/gPyB/QP2B/wPxB/IP/89wfqD/QfmD+wf+D+wP9B+IP4B+kP8h+UP6h/0P6g/8H4g/kH6w/2H5w/uH/w/uD/IfhD+IfoD/Efkj+kf8j+kP+h+EP5h+oP9R+aP7R/6P7Q/2H4w/iH6Q/zH5Y/rH/Y/rD/4fjD+YfrD/cfnj+8f/j+8P8R+CP4R+iP8B+RP6J/xP6I/5H4I/lH6o/0H5k/sn/k/sj/Ufij+Efpj/IflT+qf9T+qP/R+KP5R+uP9h+dP7p/9P7o/zH4Y/jH6I/xH5M/pn/M/pj/sfhj+cfqj/Ufmz+2f+z+2P9x+OP4x+mP8x+XP65/3P64//H44/nH64/3H58/vn/8/gT8eXxdPlZtCNqtfr/UF1+AnXq9V7PSf/5sTLLi+bHmeDTsB8mkWSaNnfL6FXBF301ZKqPyQW9BhHpxF9AmpzuI/cEej92aVT1stxiK2cxLvXYWH2J+lD+ySYNc+tXdffqKLI0gH77+907BU1QsTTIt3wJuCDvXuTkERF9skbxUrnhKb68pkiCyk+9561VzocrsZspxZFClT/lBqtQls9etNMp/DQe6Fnti8TOd0aDSnh0sq99gB1WcXJ+QePu8rnWX1Po9+FThpdRvsiS5YpU/swaXtpTjBT+VsBWkfAeCzF0mcZm+lD9rH9PXl7jU/x/pubtumjhsFxQmxSixXLUxF9TTwGFDO2BhU1YA207ENMuxJFm6H1NzK+6GkMkipHt97nJRNADOCAWrFQndxYQoQ5e+Jb1KasHzle+QVN9bGIrykc7d1VYWTIVjihhgJbKQMC7JJEo5Qa9f6M3uFN+3fh8EZrHAHSxYIMkJWS4F1lJve47fPIN+TYDdCR6/hPw6nJfq21H5lxofElIrB6+D9MaFAisVbB1KDcupDdP0Zuvu5SNKeNNQrP9C47nkOuCE10LZLMxsRFG7fiNpUqGHrqZmx8ksa+ag6tCXSzEgmG1uE+6P8mbxtXpqqesTVr1hUSsHvawcTHQDQJg8MVBGEJZsEPC1gTYv86Jc+ekqafTd1Cf9gJD4uFOeiQm7QsM26WljIGQvcQZuyOyiXzgG1IP9z4TcLFZ/kjrnL4du0UhvGg6KVQaXuQySA8xjHeGkigxWOhSpB6WnzrLdorbx5GBguZQhhqrcSxdUsDNMF0+loGulXatJXrnT4iTMZ8NWPXMLmBrMMq9Q+7xn8o8jXA/mdKOv5OgD2qF3GFGk2xzhq7GLSXI0TRax2UFi0p55d5FRTX1BK7o1Xtw8gxuDmqAZTDfQ1DYn5cJB2p5udGkWf3up5zRdZpKgg48s3KrxXYntGy/5ILZVueeDSe6qcQRWa1cRwTIa59kU/Qf7NcWeihqICo9Pn+xr630wncBswp65a5YX+PmZlukget6QB6vziOjxB0dEra3MABG0VhEvwuJ0Qi2wdYNVWKw95FbZmcnouTuwHx2VS52Xup9tmVZuPCeQx2naq6EKJddMhIlL7+DnDiXZZ1yOdxLaM2xHi3BzYAUtZ49rzOBVZMJnXa6dAF/IkldxDYBkt34C6O+EFATf6wc2AfciodrFPSqnKks988TLpcke3axQwFzq5a1B0A7TnA8fGJTWwOCdOKq9Gdd+vs6jW0auH4iC/0vzrEGNmtVNsPbLQUTz5or/CirEvWH8sL9nD+rsf/RLmn8J3NBFftOpIwUJ7UzOrI4c0uJKpxlmda+/478SxgGgSWR7aqcRqVeWl0i9cjCjL2lvPsUf6/+A1iSqmVUl4gXrhCGrKH4D3Iy6LSxk5awk8SHtYUT6ncA2z87vcl7IHI105kb4LVuwS/HElezrVWbMqnOooCWVSo1dgKfHx/+lEclyfOlPPDQ3FMB3sGSlyd+9cEp+87btzzD0n85AzH2mG8yeoSiDPryRh4knkWHx1Bu+A7n+wdygNjccmgKIYl6d4ngI3nsFOyY9ejy9SSqtdkKd0ZADvYEGxozfK5ir+C77/T+q5FsPrSMxnv3jB0S4arTL6DXNdG6CnBN8HdhhZAAvjibEzpOHQygkky32C+YP5Xh6h1TSPArEXKC6ujtkqieDlovefpe46mEMKlMt+4+JuvjPehFzCBkSAYYRsTttrUiSu0nYkzu+B8XsYszmOnmMkFyndtrzxEKnkgOHiSMHQ6DpOSY21t+YOsfBuHcMm2YbmEfR+THzS2whc0tWZhSsGCnHr0E28Kgh8vM65bS3UlKo1KKHjTc16hF9n9Y39/GtCNoiqdkUQMdn9IjkYYwIojRg1CqvMzLKE6jwPCmeqVNyI6Vm+Jwiz+JbFWkZ7q/D3+Lry8PCipkvM8ZEen59MEh0qqU88/l8KhZzDHDkIchydnoC4oBggJXUabslWhqmwOShuUyQG1zSYkEaVwpDqBQbi2hQZh162X94kMGC8Kr8BQsZF+GJtkSQcfpHPzm3TjddIOavjX5fb3fpW6lOs5dOOa2PXW9eU8oo0aVwEyEkQ/zl0ii3RETD50G3n5+81km1Bx6N6YWBbe0STbtoozmCatgHIlcmA190hlZesalwguHWPjk8rEpTGWULJQYmlGCAU1y4ko1DN0fQ5vmvyqCV2Ofa/ZRFV08tSb0y9toZ51sAhFdxSDemSgAozpNHiU672UFK8pfYKPqo4HlCK7lssKToI4gK9QUbEO2KAOM1PPUDhGxVcjIwTIAp4ChUiu53fk/XXb67sh0XWtVG3pTZ48rzYMAgM0REPS3+MfYnWcvcFZtP564+HUK5OeHso8A8vOdVH5iybFQNUk8PjRLT3y5zmfDDbsEh6RjTWsK6M/VSN26G54b+qDhFRCDUOWixPCuHtgHD0brmq9844fYdJSADeZOuuD2qmAut8cG3LCO0JOIlAuSH9XV6yRs1/+4+RdpUuO6WlgOIJmcj7igo71Twf/sQ3fKgORJ9Fl7Aj7f5lwo1ci3kqqmdu1UVQqARUWI1BoJEdtQz/F3zbFXMQymdE9PiLTIN2NKZLBiXtTW4sNv89/x7s5d/Y7LjXtMwvA7Cup60dvJrhEFHPTf8AJdJmzE7ZKbs18DSmltIEAvPgpQklfwUlTorC8kK4lg3ZBtF00N+jg3kdtb+M5Oki30euXrqWrqqvrCyTiGzszXvGj39bxdfFPGcp78dMeW/0s1dUup48GpXzZauetvcJeL+AB5WTJPGX1s2mzBdnm2Ckk0bXgn+wSbVqyCXNCNDyRH3aqLNIuGU0MUPuerGcLMYlGcR/oJ2s6dp9wMN5ZMqX386c06eLmKS4HtsManka4EhuuVqs3lBlLCBRvPwxo9VSxnpK5AeVenzVBYyM96A/NdIqyNESd4vfJ/zQrWiqXYzgoSDu9BV8fTEbnpQrHoUysBeGBXXsp2T0+v2eXQIdJctpQ2hsp4mOuaVTroUG1j2n6ljiuT9/pyFGPsQQyjuL96k9aNL4f/0jvgwcKRz1RDDlgJJ4hv5jJ8nnwUyw60caNfHIcnkNNJLKAGxiY3YFG5KopKZG0Cw5BMHwJbIiea6v7COd7+/Nqd6Q99bg/3WqwtPkH8bnrWmNUwD8Bfq2lVgmkI8pwe/Mmd72YEDrhkLmupz2kxp+fQGeqHe0XRrHBm41yQm6AbRnr3wRfgULSXnRxogJ1C04st+O2LEl0AT3ipnBxgP+c8s4nsFY+t2X6ZQPH/+e0v1wfWopL1JWcfSSMm2tC1rYLzmrdq5jFd6S1hkCm9903z3F5P3MW7ViOa1GW5xVQ+DnJE84Tmo4owp/s9swXQ1zeJwtgvcHKWd6YlSAL/0iSxuufpqbQTmrnkCrOIAWbkQbmdSbdBS92H/U5s52LAmWy5uYh9GnlyAxcMapELu0WqL3P6ZWmu/yvCFdQHMabh2UnesmUInx+xqal+guWHTabKZC3oRQiXYcTGRxu+aJSJ6u7RNP4mPx4FDlxQ/16txNWyyWsCKgSCc+nkirDaMmn3FyheTnuvVTkv609Elc2XJqqnxtYrGXAvaLMlF8p43auz26P5eWqVl7244sD8k5V8r4UM6ama20rbiISO8zSaKfHqe4WxkOlK3mKDt7OUU9Zbh1VGdoSqTBJqb4vH5RkmY5BSdaUwp3cM/us1rp+AbpB4FWz3VM9ypEiFzUq2B+fGIeFX/tQqDIRV5koAlyfYRjkOTUb7EsTQbhEVSQmpHW+fcsiHVabiSYNuxXDFyo40j+863FeOzsiZdLXSJr5dpKWJL66Ji1fSpWb2rDsnS53M05qDZr0aaeH1KLVBAPqGoV9OroYjNbr2qrEubPpf3wcBXqgN6XibenCLjEM/2B2KjKymHqG+PrDDCun9jEGSMc5gBwdd+gn4tmx3RlQieZl+sweLQZpw3czj2tROtrXZGzISbgO4iPDuHBU1yr/NHqrkKBtbNEe3CkRxRPiGECDK85fJmoQPh3+4AaBVqC9tBiwt7SyNsT8wJHDImoAsF5wWp9u4ZZ+ev5TJWkotr/MuBl9DC417xQcayjZ5aZe6R1VlOm7IR3NxjG758UZ5lTvm1qr1YLWq5kNFR3HGo6emm/51FOSy2n8s2CiWWDjuJqBivZ9h0n7jB1pBMrzgdd0eoX9y7qa3hszlFt5A3yIqIcgxYtCh9GwdDjhN3teBWAwpiKn9INmHAPlTVY/QWEw6uAKyz8q4ETLEaDN3fB9TLJucCPZ7dHyC/qF+ie9Gs/ZdWl/wLZyBlXNYlpjY4ArF/S29Q2PitB6gGaNUaj42WhFDsA5JpQNdv8oZLmADiJBlJw4gonNB3XurDTn71aK07ag08wGfV0xPlGtez+FDB7TbPjou7c2QlZMoZyBD2M6Q0ypiO3OpY9KyanHARrCR9yDVAxVOcvX8cATKU+DaNFi2fTS+X4MDpqTnCKCv1
*/