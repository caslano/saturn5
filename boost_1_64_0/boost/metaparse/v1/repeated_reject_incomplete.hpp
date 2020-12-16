#ifndef BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE_HPP
#define BOOST_METAPARSE_V1_REPEATED_REJECT_INCOMPLETE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated_reject_incomplete :
        foldl_reject_incomplete<P, boost::mpl::vector<>, impl::back_inserter>
      {};
    }
  }
}

#endif


/* repeated_reject_incomplete.hpp
Gt5Lohz2YJyWe8lGnjsA13LcZNpv+/kMA7d7uLMM3K6ZzjZwuyc71+jJVFP/+QZu32e80MxhJxq/uttG6fSsUazXz+yB+Uf4dV5aY+5zm7jEc4F/m0mvKmB8ed56vrnLvQo28KpIRwQfW81Z+DWY406ZqPaBwLdlPN1vCD3aKvDsfvGbMfXbNddmyGLy+Nw3Q1yeXU/eWIPzTEOT4IbPHYObamx7/NrStufmHJr8szRvqdE+AZPEWcWuwN0VsFu5n5HmOZzPEmneNvvp22rUOTLB4TPK41DNrVPNuJzKcKwP48/2NqL+ElP/T039Jaj/Z9CVXQ3+3QZ/V+DfA/xGg3+fwW8E/v3ALzL4Dxr8IuA/ZMYt4QGO92IE/LmiXPjDQj/3MnVMRR2PGhp2Hf0YeF5peH7c0FsJer/VPBOeXv//ztRn4U+hvvmmvmdMffNR3+91faRbeh3/rKnPwp8T8NKYfffzWDPuItaMW2r0/uPPNbnltgq6m2Povgi64wXdlwzdv8XQfdm0x841rwj4oTHlXzXl7VzxGvg6TJ5PGL7eiKH7pqFr13RvC/htMfJ4V8BPioG/b+jb9e2/a4a8h79kUcsyEVFCpHGeGNS69vF6dxSlqYauzp6jgyidF8xz6ax/3+haud4dvo7meL6al9Fl9OZFyxbVzyVn6wX1yxY1NbbOXzBvuf8MPwwcfOeB74aR0x+aMmiOAc2tkIV3TV3m70IiPTqopxu85G44j053l9FX8fSirK/2Tk5WBKdrdam2rpZ0KsM+FyRnktXS/t4U3e5dQqeJA0s6BzJ8ty4/WOACk9T3DvZkcC6IN5/cjbt0jyPlgQwrCRr8mSN4S8TztrBzzdosTkXQ0tfWnz6sqXl+0Iw3jcaK/kz+j31zBmS3Y0hzfrp9cM0iOkyEr7qTj2u8bwnySC7N6dRg6KGi2r9DeJe0aYP7srtsrbs4zWed+SGdljRtXNbC9xPyaunrBJkG+BzuItpX8l/phl8DVOfpNfe4Wj0O3ynitTbDadyi7O75Gj+f4KBNusPrCXevsLAWb3PUavtDeNROfXewGLgTDG6hvdNEuCWGJ+JVwUslPABc1JVAXeWo6zP2fkO0Ty7V9xoyfm/c259Jd8hz83GuDDnidvX6WA/n5of+pHTDPQh9RnckpipF/xVlv7WIjyzwMcF8STxzvAruD9J/8F5dK9bDwCdc96P69fsNtShTV6vjzBN9+vH+7Vzh40754T27vWr13mJuEAzh39XSvLQ1jNHQtyF7bV/m8d58ci3PTXvXsm/pFNP3+9TSz+jnVLTlY8CdOiQvaxqZC6RgI/dFWeKF/hbndj6fz+1Q9/TawJ/boe6ZId5240nJxnNHWwh4mjVymtSUVFtqbZppWghozq7V76d9ImyHq3gg5MnlfTK091mSuP8e6nk63eG+cvm8TcTVuOy3qjVBlJefzWsMZkLXD1C67hhbMW9uywLuDmRIv6rJRvYH1uq9yUGQ/RzgxeugFAJXx3msA/OEDswTOjDf8LEAfNRDBxrAx8HAa1ZxNzqzdmFMcfitMMDfJM/1ActRyq8xQHmSlf9mNRs2f5G0+SMeXzSmTBsOQRsORBuWoA2HGrzpRuZNwFsKPC8fHq/NZry21NLPjNdloLEcuJPj5AVZ5LFcSF40n8G/7zAhh3HbGdv7Cf5WGf4+U0s/w99nwd/hwN1T8dc+c0Zre4/uU5+ejXXkkXIdOWL9w7vyRt5HgZe22mH84Uc4nlKmbztMXWkxb3/SwNbw/BnajLkKTvGAGe7okqxYvxz86Fre91Fe7LlKt8GhPqef/hbVa/T2IE6bs3pz9gk+B0wd1H/003wMsj6A9+0=
*/