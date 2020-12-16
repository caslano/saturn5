// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_COUNTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_COUNTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <algorithm>  // count.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/char_traits.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/pipeline.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp> // VC7.1 C4244.

namespace boost { namespace iostreams {

//
// Template name: basic_counter.
// Template parameters:
//      Ch - The character type.
// Description: Filter which counts lines and characters.
//
template<typename Ch>
class basic_counter  {
public:
    typedef Ch char_type;
    struct category
        : dual_use,
          filter_tag,
          multichar_tag,
          optimally_buffered_tag
        { };
    explicit basic_counter(int first_line = 0, int first_char = 0)
        : lines_(first_line), chars_(first_char)
        { }
    int lines() const { return lines_; }
    int characters() const { return chars_; }
    std::streamsize optimal_buffer_size() const { return 0; }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        std::streamsize result = iostreams::read(src, s, n);
        if (result == -1)
            return -1;
        lines_ += std::count(s, s + result, char_traits<Ch>::newline());
        chars_ += result;
        return result;
    }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        std::streamsize result = iostreams::write(snk, s, n);
        lines_ += std::count(s, s + result, char_traits<Ch>::newline());
        chars_ += result;
        return result;
    }
private:
    int lines_;
    int chars_;
};
BOOST_IOSTREAMS_PIPABLE(basic_counter, 1)


typedef basic_counter<char>     counter;
typedef basic_counter<wchar_t>  wcounter;

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_COUNTER_HPP_INCLUDED

/* counter.hpp
LwcWO28HHnDyVZqUXsn8PZBDPic6Xw/8NpCrv+M9up97bBG2LWNpy6Sp5bPi88jVSmxHPs0q7IjAJmc3ZXs2UOC8ExjiNFCuJ+JynA/ikk0fkdrHY68s0iD2UGyczmRvppkXckFeVDzajqsR/cx4ZabSPXrqq9JyD+9S+5Y4yYw9xUj2Ef2H83kG7TGd7ZflOnYhin6N0Dtf/a3CK8YxgvytjxH8PAsNAvq1WzZ55nmu0p8zdN788ZMc2Tc2K7xv3Njwvpe13NhTwvt+0L5vvLKpYl+bKpP6SD+mjdWV+tmqsZ/Wa+tP2mYBnbKvVj3rzFa6Y109p6PvuUXio+8iQhphKeEJ0lqWbe8vpRXjVnd2bahR8ebx3CHOOm6Rrh6Lpoe+8U3nto5byFrGOPu4pWXNtoScsn0zbEUuNcexBhUnqO1E7lLb8U67PAOfIf95dTxVj3t9pF19UtpMQjfHPfTAPlcPMu55xkLqU5VD6rPD9WaX2Jx8S643NxKuZrzbb6k/sf0Uv2y0HrvNCXG9/tSqytZLIwzrYliOKzPYWm8SX7cRx9NG3lTHv+is4P98bKaW0PBKKEdf9Bm/Pm1EUlwwnUeilvmafJ9f5q3fYfucPNosJ96e7n/eqvyxSflzTL9Fupwe/4x92m3U4sRGbTM6bs6J1HFdZf1Y96PXnfWRR1S8U53+9mu7pBvwfifbqmuRVbZn96DDA+4zYPSYlooW+wexOcsq4L8k5G3Xa2/f0jaFP1Xpns61MKHTucADSi6zgz1aRn7X9mhR+0Pk98Z1Wx+VIc+eZUx+nrAF2cJcXQ/ov7qCmGqK3avdB6G2cT5RyT7K9SjBpnvSss1HrbpH1lJP9vEJWW+foMiGvueq4z8i3UTzO954/QzZVR+m/5+mZFoc23iWC+9Vx+O0n/QH1fZY1cdm0oZ39pU+1vgd6WSd9DGJ05KODHGCucXBSaPbv+/cj31jkNlFGvcgs7cfMoFZafGkm9grKSl+ACaPGYTstKFpw2mBiQm2cdPb/rQv6lUq702yHXCWqe0UX+O7vhapOOcxB4+TfZIOT5H7sj/aOP91JZOkfT6HbfWz8tvnBymdzQ86+n2Udm3eS8g4H9nW9Tz2bfHVVyHtZznhC8gW50W2dXMe+zlkaLOq4Vjat8QPRB2bFqvjZzkz7TbOOv5w6r6InN6QKXWfkJGWlHZ8WmWo2oMJufyXlOirzsN94DyV9lxGxlRf9Ryur4vyOl7Hd6jthKj1e2lee/2a7dl7DU+Jcg13dZwtOpa69d536zErT74bv1muz58lfJH4LZH16Pv6TNxO75l/o44PstUfca1jlo4b31/5b7eNYcSNOi+w2W4i3/k8oFUdv8yZL/OAw7SlJVkyRpX6mQeE4jQSJ5s4wfxh7qWuwFwPMPtvDjK5+V3PE1xbx8H9ta2jbd7gu0/nsC/dPr/Qa0jp8r39EJAjfIk0avubbaS+lNjtfqBp0ivrV/laQyIdzzcP2vtDJqxXxzNt7YW43V9/Eh2JD3XO6fF9mSLfff9SgL/htfAzrr10qNwhu1K1zOIqbay2gSX/bKMvdf8n8rSiXCSKSUmXXR8LGLa967Rtb1N+yFc2T9z1veQ3lfynAu3yH9W21vFKPi8wjnuEdwgZgcQONsMF0q5vCOU/MJmUtxMuxn73skDHeVR9eU1FpVvncr1bpNJ+0LmJXN+LjvJps4mOMqbS4ctu8GGrG64LN1/Zoqs+HfatU/eE31b55B0jsYfd59lOzu+4PUu2pw4Iba/0HN/u2b5Tb7fb1+6Ki27HabejjW4Parejjd0O9doP3f1nnfLG3tsKL9ry/rln/3rowksPHj17WbsdcHQ=
*/