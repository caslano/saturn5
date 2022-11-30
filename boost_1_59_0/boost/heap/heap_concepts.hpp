// boost heap: concepts
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_CONCEPTS_HPP
#define BOOST_HEAP_CONCEPTS_HPP

#include <boost/concept_check.hpp>

namespace boost {
namespace heap  {


template <class C>
struct PriorityQueue:
    boost::ForwardContainer<C>
{
    typedef typename C::iterator iterator;
    typedef typename C::const_iterator const_iterator;
    typedef typename C::allocator_type allocator_type;
    typedef typename C::value_compare value_compare;
    typedef typename C::value_type value_type;
    typedef typename C::const_reference const_reference;


    BOOST_CONCEPT_USAGE(PriorityQueue)
    {
        BOOST_CONCEPT_ASSERT((boost::Assignable<value_type>));
        BOOST_CONCEPT_ASSERT((boost::Container<C>));
        BOOST_CONCEPT_ASSERT((boost::EqualityComparable<C>));
        BOOST_CONCEPT_ASSERT((boost::Comparable<C>));

        BOOST_CONCEPT_ASSERT((boost::Const_BinaryPredicate<value_compare, value_type, value_type>));

        c.swap(c2);
        c.clear();
        a = c.get_allocator();

        typename PriorityQueue::value_type v;
        c.push(v);

        v = c.top();
        c.pop();

        cmp = c.value_comp();

        // verify tags
        has_ordered_iterators = C::has_ordered_iterators;
        is_mergable = C::is_mergable;
        is_stable   = C::is_stable;
    }

private:
    C c, c2;
    allocator_type a;
    typename C::value_type v;
    value_compare cmp;
    bool has_ordered_iterators, is_mergable, is_stable;
};

template <class C>
struct MergablePriorityQueue:
    PriorityQueue<C>
{
    BOOST_CONCEPT_USAGE(MergablePriorityQueue)
    {
        C c, c2;
        c.merge(c2);
    }
};


template <class C>
struct MutablePriorityQueue:
    PriorityQueue<C>
{
    typedef typename C::handle_type handle_type;

    BOOST_CONCEPT_USAGE(MutablePriorityQueue)
    {
        BOOST_CONCEPT_ASSERT((boost::Assignable<typename MutablePriorityQueue::handle_type>));

        typename MutablePriorityQueue::value_type v;
        typename MutablePriorityQueue::handle_type h  = c.push(v);
        typename MutablePriorityQueue::handle_type h2 = c.push(v);
        c.update(h, v);
        c.increase(h, v);
        c.decrease(h, v);

        c.update(h);
        c.increase(h);
        c.decrease(h);

        equal = (h == h2);
        not_equal = (h != h2);

        h2 = h;
    }

    C c;
    bool equal, not_equal;
};

}}

#endif /* BOOST_HEAP_CONCEPTS_HPP */

/* heap_concepts.hpp
ygsWnaJQc83J4jn+pLJyPa04bg/+cYSObSsJ/xw7PQa9TWiixSCruk9K6BD2nuWebJ+IwCqmlpo5lgXw3TvupQuyCSLTEYBLMSWSUT5IhJDTQocH6fCPVuEXCKb8qs1w/7bT9YA4XvRsQLxsL/dGmJtBg8casnCcmBJfrHMbD7sdn7NodcTeZPa8DYOVA5S/EJT036DunEjlG0TB2jLpmg3vbayZYJ8dwDvZF1TbVK1qjW4OvKk/L+tLp73nEtsmi+3cYpyY4/xN8ol5RhXSUigwP2Bxtz+wLXnbtsVjLJaAyPGR+9YVSA3Nl2kqK5o+fxnreaZ4usyDDRBKPJA1X7pLV0WsObI9+FTb2E4Sg8SKlL4sQ+LqoA/PmQ03HTMBaBHTNiKGxd5Il9RuC003P+8XqKCsJG68lurJFidWJr6tgQa14AuwdL8prJQthlky8dxvX0EBPoUop5t6urNfsm3uS1bXcJC4Wljm3fQexSs25ayIT6/T02JiTbyqUt7u580babKXB7tWhVm0XzB+dONPvXBlxEWRcAmhEDDdQs/VIJ9wH1lpcr2mpzpr08/XIGOEBOM+1cj8GZVR0l6ksXnOtwnOTb3lFTJ24NdqRndMe74Dda3EYzfT8zByljUWrrSfYdlaN1t4Cm8IMXUBl0qLsTMLehkW66+Jozu6wl0xZwO28GkLAfMEGnIvjstO3Cx4thm65fS/LOlYBLW5VY2qD8l7khFFxHLMcbqTFrzWY0rE2CDTCXvM7leUQ4CfW6KcmnuPetvZWhd2UusvMnvTLpNGe+Sf9haOCODJ1cAor423FDtCdxN2BoRH0eZJxUrtVLYH3dRys2/PFcAYej5koq+CkQAB4sP0Dn7RDn78L0CdB0DQHn1c6wqvJrF2cTOGvLNOLyRVln6CUjzw1I8+XCGfS9fkf40lX1JRLkmjAvNHnkOJjtXQPnN8dWZmFeig9ukjtatYlkAhwsoRkxC2y7NZNvwjyDwV3bslxNEsG2HhJ2Hw8x/w+2q4+nadHn0Vdw1Ca2IRSxRmGGyZS+fIlZ5tUBY5B7u8snRQZw31zHEKpQdB8u/oG6v21+TSQoOFjyfXV+5YWDkJTHX2638oCYJ77h7iNaPZlUpbZUGEetM1iOTM5wyCRncxrDjPL2h0eloersrvdQH6OfVdVghnEhPZPQtGn4p3JwiqHbEz+4NOypKr36RzYCcGQkk0BStF7PlqF6z+up7sH1X4b68ISS/pX3smoYWzH/WG5jyUuS+Www3Ae+p8iq/vN2asYQw1BtDPBuUPWq5aVbeo21/kUham7858tzQAd72pU96p040i4V18Q496EclrAsAVnkiOcfAUIRrPst1d3YwP+/avCoaynrYLEAspR6fYOv+yX3wLHJOO66Ty4TN/38Ys8b/K6aOV54ssS2+InJZqJTp6z8bKK5F4Q7pte8+jp60/eftvSAPF+5ac6WxWS4DV2ObR3KG+swsb/jp3aTRy7VRpJFMTAq6fJQo4XTXJeTqfL6dtvbvfqkl7aXrKAlfr31MvcGcjMKjNQamp5msZkSCdIkCv5kE/OyHXoo9dr2MjeN3asrq6EHj6Iyh+Vd2Bw57MDuVM2SvzfhX4Y4aup0KuJYeuJ0C+zsUMhLr47U6Zd4Z8j4VYjluc7/nQ+OyBelmL4zznHhed0721xRKvHADp3SuEN3NEqEeCGtL1RZn9Y4vNlF5piSi856L0Fw4DvfEP7u5Ro0xrO//CV4RmHcACZfbV6MiUiQ/cj0ly9lF8u4+PqTd38Nyf3HNYdrP/fzELKzNYvSyhU7GIqR+jIed66NWBc8zbo4TrmLfNOZM/h7V1l97bNRMM0WOUgPg+L5t41y1/ABaY7L2vllG7wiIHzQZw8PWH9089BHQ0lAENPpB5Df8O0mGidQErKCaRx9Z77envRJNUDXC79EsjJlekm002iTFzli7hyG5Dx17i2pYAHkuFlm4spjxaxDlfB5agfm25It005zD6SiRfHZM71y1lIH/PubNvp/CQfWXQ2WC9Y5SbEcbXltsm/dxf5vFUHDXPU71dAtDL7x4nnBlDXbF9KEiCPMOFsrDfrewNsCfoyptGe9uvz64kwRQY8eDPW73CtNJvtkOWjtrxvqQC679OAq3RPG8h/C964raxb5gv8qOe+C3pZzu2Vlz4e3XmbhjK3DjbG4eN22HTpIIwsqrguv4ugXM3WB/vc4CjsTzUmGLKJQIDp+ZastOz1J+whaTabwe+cgyEx3TAzStwqnF9k3/rNlmEzXgFDYlPBp8r/hDRatIKBcbGvVLuBT/b4/lctiH07r6/G+YsmH+G7qr7DhJXNoljCc+T8ZztTxViDvqR5zvak6uXN9KkiGAA2psrTSRNfE+B7OteXgTwKo5b8GZt52yDY52KbQOjuwKjpb8yhghlNIrWCkSJ2qaGxHzVJ170nxdkF18mv0SnzvjogdLm7KeUJ8odEn6Ewtnd16tSMHhoMncbaYSkcdiaU4PlZskyOqhivnI8SF6Jguk/4wLQfP7032XoZRf3sny9thYT/MT0Fp67sh98MdGb12kZd2TCfinWCQ2iVM3Rgzu+beo1hG4TlWT8DYr/ctZ57klUbAmUacmUIafaXeWk4q1AVTirfGcJbnmU9Hba5VjBuKU/uLOK2nYjp6yznNxYu3wKwDBpZLovd60jeeEDv7+ROGLnPoe5UZPnkjgb2tQ+65Kg3FfoNdwhrZvb03LgW4l0DrCVcMsSToMkSHio5SPt7w819sqITf/XvZ8PJeV5jQtiJ0iYsyVlO6KC5yPdv38BzzS6glkkWlBywyB4yFiFciEStWYTdzpqbGGm3Qm8dyBAW4d5fkZ4vkS49/Z01RNLwpoiGLen8aISxqQxgTJSH62NLCFgl/qZV57oCQPrlyy0pBcZyBkCnsfYVlvXSXmbyLmHlRizWeVzjTer7S60l6toovHv3Jwpu/Tj7SbRXZvjrsrtIPDsfZxdOcUtobnsDUjtKhrXXWnefzzsUe0K3O5aDMwtPU+S/sA07QDtkuKjOWZdPEsb/wRxBivqtyf3+vMUHLe6K9iOfk6VbG4+AbOI9ZUNXagG69x6h6u7viO77edYcPcmHa5OPUjFyvBFAi3E/7joOquaN/6hNGxbF7irD5nbh8DGl+YiotdYMzVpXXzrV2f1l9kxbnFp1cQa792vujlwnNJU2ir2eOBjmzpfsNad/FbXLs48J9SyJuatoxLgs/4325Z7de45wUVHg96Idofpqrmb/Y7bas91zcmbY0ZsRKmCkQVnSmlTD9vEc5HyP1PJMqH6D7YI/fbIKHfffhywTatMFyDJw+VMGS+c9RgAACz/076Ylgi6Nv//RT9Pff0Xm4urZcPYJO+A5i56TKCMiquIlWgWQqjcPX3kqZ+nCcWNH25ocwscZA4ZhHbOPiZNGEeNIPENj96AuXt3SbILKLcRKLcwHiXVjfobLa00I01dfDWLKpsDlC6mXcRxJG2Afz55F6b7usuvPqmoSy3AO4zndJ1VYKQ+6hc72vEd35L+lA3YHS6Nl34AGluBfjBjubqu3SVGA5ob8XKz3QFzpu1hlSI+qbR5d8y3lZV/Tdc2iAy6shiueeezwWjaDf6hg+nPBm0L5n1+NgcI7TRjANbh8uvGw4pBezf9ddv0SXF1QaF13n+gFRStC5iC1gs98o65LkztIrnDz4d1jfnHLKcekbl8L3qNDDnGTQwbcbGtRtPuWIPqmP8j8LWpei6TbTGZbc6VbdGW7d9LHExzwbz1WL5k8IlL7FYvy1fT3iyFYT/5OfjNK/AN14iAPW229Xll2FWiaWeUdXzsmVq8JU3vAf43j2vZjSvq+cgQXzFXa+CrLdta4rjjxks7Lktpw9z4p7of6Nd6wwFNF1Qlltmo0i5GTrA5vGPGTvmk/ekqnTT9EwcCz06d0e/O7FVu2a6F7RnJ7tEDjtzV0jR6Bu5ZS+pj556ZA54ZKuhF/6OuE++cUQQxhSEH4T/1W0iKVV03ubEiP++uBfzf7PNZktddYQtemXx33VuGJiKmBWT/blAvYWHvTKuPlvsXeKPrTrL6cfsgpFyAjOb9JDOsKk+j4dXYGAyornqkhu6Kuh/G0y9ranWN3WapR/4f0vfVH+CvXRFfbT8b/+9cEUePycc3Wxc29Hceg3Qrcr6/Pom8cyOni/czpqA1s007jQMdOzDvt//oEE7njTLI5o5Zt4lUp52IXCGbn+6Y99wpMp1Mk/x3iilHvYDfP8EE4vPl4X+r6zs14djvvfDjRBqrHVLm5pMeBNyyB3D46s4bgpdHf91j6G6gb7w/d1yJcz8YF8Iih5t6PB3/KsiPtuJWJ+T9fmnfoJb1j9xbqIIzJTJWM+aAjQgb5E7bw+tb0xxFTSVKZl8fZJmgOa7NgNg+HWiih2GI5qIFJISchjxYwLvrT8O8X8G8V5VFBeNXqNeEiiU3qqKz9A2dcuXtBe+EX1QsJFvC4M3XWV0r1wnZKtP2uhXP1CfUrMlaRqVrkoVQD+tA2+aELhsTl89pGKHIgcvSoB74ICo1N+JQLdmeNuIw03qCjE48YQzw0xb3FiVV7TXqypTqCJbq2M6xd+oEVJaJe5hhL1qy6zmPliStD8gyA+Vo5t1sLiVGp+ZUOV2MT1CMVj9IzCryabhPlOJfwbokORAR/J4x5YoxUCjBnqUyM42q9BmrRVsVVJ0rXyXuMAHH86weuq8K3un+25vqdIfmdKfCLvHXEbDh7LuF0eXSLrrXtZJ+kzU7ryVY21K/UMXgWnudy9E8MQ7HAAurN9UTgNajyTMveKZXXUKgJsXPktwwNzuGD7LKANh2rTI9DOkK2ayO99EDc6G4Un/SPM3/IZP+0D/KJxCDezccEtmG+AaMvbkYy9l7tSKzd0Chx2JuOxQJ3lFIezoe2dfYwa3wEIu14ph3LP85bU23Kz5v7ZjPqUw2Qc0HAGhVG+J/f8VVI2qa+bySCAq2E9cHZDe17IcqNw97D9CsyfwPIolei0tPN8uPuctX2WhX2c3W9udBb1SL7kdWU2q+O4qv9ykRP7JwjNsP5CydXU4YOgfjR0iUD0utGjacs9Uo5vEW0sVe5bBs0nTYefiBd+hroO1phfr+0zZubonXSQ/WOtOdRnoRJHoZB2MYB5wCgz6LAazo4TzjODKMlr2Y4EMs5zXc05jfXptP5PlxQ79LxuNDODZdnkZcrejgHN7IdpXb+qgUI2+cWeSEjnB2mPo/xo5e/uoA7V2j7nCJjGIiFch0QOOpkSSvuCGV8OIHnbWhSDxKBX0wnbaw3tsnMenUSKKgq5EG49tmCFVB3Z+/nf5a/q0lGFPY6LmULFHc+GU0Ncmd0dnKSMYod752r/DX7tfvmwStkj46gpcqbDmqqOryzlZVIfOtT4O1lizMt99pZtIueQZGmFD4+/y0aDvvOc8QrnicuSP+Tykm0ol1uVHy9tHs+uQsUvuTuq9vEV/FsFf0Ov93M6XRbLxa8lUspYiFzSNifd9hglkG10I0T5tH8FsbwrezYaRN4KqWYKrFT87Gn7cQVjd1hWU7ORyTRyGk9CW5zi3Ur/gFyrK0B2DPSEBYDEimrqI17T5680jaN7eiqj0c2WU/k4atmqd1MJx7KkaDp3/7a55IV//KfQqA39fPwUI4Sb9m+Gf20/ufc/8xe/RCyKWEQlLrHg1VWzzflHyCRFG2Geg32o0R5N0Q1ZVpSnsvwUAaNYmIOXHl5UU0sCmFhL3hXFN1Pb23mdbfyghg/109atA1DgfoHU2ckuIKDZDDczkNnkOPoW3iZAyLqYEo0dHJcF+86ZnFr7fiKSU9PW3jt0sBrGraD1orFvTR9nAaCI1iXmlslaFWsrVmYWzEVOzv6pw4gIIBmuGRkOmj0IYBHDAjPTtL908lMdguFBqcGB+UKDk/um9w5+ymiEr6XCNkyDLeXXivygS5nqcRArmCebOEyv8qllRwkRJ7jkGOJuKkEnuob1wn6tk6cknUex1pkEj/bBrAFBwAjtUiCQuAcW9wc8DMDA/cEM8OPuyeO5Uu3osCqPlkuIaJna+XrUKc/coSrtljiD31gfnB9iDjCNLFyk3CPbGfbXmQsGEm2JVzqx0r4in+EmWM7i1+guuKPfljXclzc59Bc9nD/Dr+9y5RYstq/wMFropyH5Yg1SC9PpixTQjDsjAALYZgkKk3VT94V6r+80Bjlcm6tuX+L8FMnudUkdyWNdiMKyaFXcic1SnktJ3LHFwPWUMWS5VSKdQBjTXcdwrWJ00Zs6CbEjOGZZCjiW8CYgTWCrzpItaJXGanfkxuv5ygNSX58oZS+kTGHlzLDVwLXVgChIjE4cKIMx8KlYMwoebRhxDqFGAxMVlnj+APhrtphx0XgcDtn1BYLNfNCnqhV5xwN0/6gUmQlpoSYDkWXrIhY1iCc2gfI54Bru8z3mi/3pZ9MMePfzjt7HOpiJYAINaKW81VzHJFShuDmQgexcurb+UIf1HMIZPbycqQd5dMXFwlVU85pI+nooeFnFZNCaJOCS4ujI5k6PNllBy8CJzJLh5/BjkfQM9cZkZwZFNZEa3IPVJMN+JnD1pChu4B2jeJ/edadoiborHyDRT6V/FKIryyBPhkCQnIlMGCsu5EeSIM271YaBNjMV2InYhgwWmOcgzdBZ+fHfxCRMFpxU1scvRtv4y/fRaiQh+8QIZDblxiNBAOOENWS4qPyiPFgxizz+/iV3neK5v4x2bKYX1BrhSzBFISvlOHLer51BfRSHTPnCJOOw46HcpmZVCGTZ0DeXIFcjB0utK7CAbSA1DHLqBN9DrpM7tP13auSx7yv2y8nzKb8r4gZ7YIA0dqapuoxl7CvdNZwg7dbAfrg7082ww1hc6tpNwGBNb1o5YKUz28AnsWap+gVJcWE347pnjphiwx+pSpx96XIxlsy195YNAuz8O/XYvAOVMO/O4S7/Fuofc8I5rNXX2rOsEd/fD/3np4X5szNZqtGyp9w5xlenSEo8iMXZZJCqp5uDdDO5RBh8kOKuQmvecR2ZHm+Jb1dvJCVeP+JqtxoTU0GyXWdmrC4MPvmDQO4pwpDZv3aiuctj58CK0hz8JG016ZmQRwwP++DClN11lgzBG1AbZ992R8paM7MRLImu+qWrurGDCnAZCsKWE+Mlf4xfAV38uAxvia99Wb9dl7RbfiSdBHXcOy4fbXN7oh6+Zi9avijKviRDbaiF1kJ6C/P7ktph3Wf5BYulT1voKQL1bptoEKvNJ1QESVbt2ZiS+6Ygl3Rrm34/+OSju+dG5lYlFhgJYJHmQdJbaxBWvnDdjCt87dUD87NBIlaF2TlUzk48vg4wuwOt1GDy3qmM09ie/EcTfSys7A9eWkELyzHJkMzzpmhAVD8DaZ5dvXs/WpDVn24Xf0Q9p9i88XwvDP8aOqXqOAV+aHmXWTOIxllrm1T8jWc/B5nwQcvw3zcU76cnoN2HHWqukad+8k6dVizDj7+n7p3VSaDRro7w7EgltFER4arLHxNWzb8wZ4nTAy+lWz+lmzKlslA/8HWiwBPkIb/kE5RB09RGJ/UeRvxzWTvHLdCYLZQvT2m2c0opFVtFX+kOCR0GUWZasoYCu4Eu9t
*/