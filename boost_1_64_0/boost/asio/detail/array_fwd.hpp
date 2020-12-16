//
// detail/array_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ARRAY_FWD_HPP
#define BOOST_ASIO_DETAIL_ARRAY_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {

template<class T, std::size_t N>
class array;

} // namespace boost

// Standard library components can't be forward declared, so we'll have to
// include the array header. Fortunately, it's fairly lightweight and doesn't
// add significantly to the compile time.
#if defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <array>
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

#endif // BOOST_ASIO_DETAIL_ARRAY_FWD_HPP

/* array_fwd.hpp
EtB92UCn9oJ9NwbFT0h+YA7jWnAQ8w9w3xSwVSAvZF3T1fsNAtdBgXpd/m8n8L85d4lTDeDaAM/gvIDcoXXVuXfZf1fj4DuiesqxL9r/3Xb3CKcaQQd1Q+6v+fMvALo5wPPv8yIkaGlr4HllgGY3v7/gH1OilUmdTOpkVnC+2LkrcC19aJ9JXfD7WD35Tp0F7rw5SP8u8xWaB0/GrnWdX6Do3NX8H7pePEJ/Tkim/AIp8K6PrvPCyEuupmxqH02FziT6sX1dYE/KYe++Hhg9IG9rnLKWWOTmnm2yuWdbfvDfep37Fbvz3dfAs+vOPQ6BZ8v4Ksr//Y2+Km12ahEouiX4XRQHvzXRZblC83jG2XdA1pIY5I1G3igj7+JgeUu7+q5N5/7HDSH7HwP9OzBeZnCtui7wzrCAvQL/rdu8zKkvQAcyBY0N/rw/n888vi4gfxd5Ie272FNYZMYAB2OATak7/HNNYM9vV+PfFX11xb5wXczYUXBByq6k7QmbA29nCv2/b+Dcb8vd0XIvYe158Pm0vTx2cactKxXS3qz9iBHX4tC1X7T/mqh9rFN/AlE/DugayAueFyK7WPsd/fouIQf+O/y8/U8vjYxNwfugiSP2TvjfJ7l9jlNns9f4iiBZQvPCzPsdWYey5j7s/4ru5U5NB68dattD6jJfCs0LK4tQGTbtx9iUhT2xZoA28rmvcOopULo+QCM476hjXMj9d9+JTv0YrFgfJOu3yPe/a5r5xhP6HqXQ74mOcaod7A+mF5J/pP+ghfbHwLolmnEuijEu6N7xxJ6aWBEJT8bm2U5dBppuDdgqNC/0WiL0ejUwT31zvWq51KlqsPHWkPV+aJlfl15Kau1qvD/Su10CMez/fpGV8x5hYhwJfM9IICJMEf77bWGKaw0q6xOmPubc9KmKaEV2rqPNO6UWB303t3cP9e7kUR0472POM6THf+b083l/jVNn3OjUX6Jc/lQ6KE+dFNr271JjM/wQvfjgt2HMHoE2wPWgHVvZ/deDnXS+fRrniOBZKPsEiD0H9BysdTrlPvVmp3YDe7RL/l9A57o4/3vdWJdXkLK+7myzZa1T74HSLtp08jySDn0SeyuRtXAifczebvN10jztFqeS1rE+gSZpgGYDNP1yhHfKcfAdExGyegHXMVZrUOyH91B4mC1gA/PsqOJBOcI26RvrKlDmt3sfRZdREpwfyk9HyNOx37Hfsd+x37Hfsd+x37Hfsd+x37Hfsd+x37Hfsd+x37Hfsd+x37Hfsd//y2/IsMJp4revxa0wSc/GfoM9j6TJ/VWamoa5FemQlg6Tbm+SomZKU0ZIN3FcOFZKKJd+7JJW9pOc8dKmBqm8StqSLY0tlc6gznLO7/RIH8+Wfu+TMqulfpXQsUv31Ejrqbu9UfrVQOk1yh3QeqZYetop/cAihc+Rjqd9DPXiSK92kcJrNpKvKJAeLZRcydJqZBuWKT0Az+3wnstxBm0ikPXiVmSZL/3OLT03VLqXuk9B5zrOo6B5F+m5LdInOdL9k6E5BHn6S5cjw1UZUt146SfjpLNSpZrx1KmCDzzvIW8p573An6C7YqpUe7z06zopFZtV5lFvgDQoC33c8IXm2OHSG8XoBm6bRv0kaW0x8g+kPjKPT5CmT0EW5L6I8nzsYclDXuR3T5KiJ0p8Skaxo6UBrdCGd7806Zyx6OiSiuF9GseF8+EB36ha6VLanYlv8qB7PfTfm0B+ivQz5L81UfqS+pcjhyh3IuPbtHsOvV/m+A6Ov8Zfu0vx9QBkHIQ/yV+JrF9V4LNhyMn5hZz/djK+IyZenwG/OGyQL7losxsfhY3A3iXYEf7p0DqlmZhKl9YVSQU=
*/