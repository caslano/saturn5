#ifndef  BOOST_SERIALIZATION_BOOST_SERIALIZATION_UNORDERED_MAP_HPP
#define BOOST_SERIALIZATION_BOOST_SERIALIZATION_UNORDERED_MAP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// serialization/unordered_map.hpp:
// serialization for stl unordered_map templates

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// (C) Copyright 2014 Jim Bell
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#include <boost/unordered_map.hpp>

#include <boost/serialization/utility.hpp>
#include <boost/serialization/unordered_collections_save_imp.hpp>
#include <boost/serialization/unordered_collections_load_imp.hpp>
#include <boost/serialization/archive_input_unordered_map.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost {
namespace serialization {

template<
    class Archive,
    class Key,
    class T,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void save(
    Archive & ar,
    const boost::unordered_map<Key, T, HashFcn, EqualKey, Allocator> &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::save_unordered_collection<
        Archive,
        boost::unordered_map<Key, T, HashFcn, EqualKey, Allocator>
    >(ar, t);
}

template<
    class Archive,
    class Key,
    class T,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void load(
    Archive & ar,
    boost::unordered_map<Key, T, HashFcn, EqualKey, Allocator> &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::load_unordered_collection<
        Archive,
        boost::unordered_map<Key, T, HashFcn, EqualKey, Allocator>,
        boost::serialization::stl::archive_input_unordered_map<
            Archive,
            boost::unordered_map<Key, T, HashFcn, EqualKey, Allocator>
        >
    >(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<
    class Archive,
    class Key,
    class T,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void serialize(
    Archive & ar,
    boost::unordered_map<Key, T, HashFcn, EqualKey, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

// unordered_multimap
template<
    class Archive,
    class Key,
    class HashFcn,
    class T,
    class EqualKey,
    class Allocator
>
inline void save(
    Archive & ar,
    const boost::unordered_multimap<Key, T, HashFcn, EqualKey, Allocator> &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::save_unordered_collection<
        Archive,
        boost::unordered_multimap<Key, T, HashFcn, EqualKey, Allocator>
    >(ar, t);
}

template<
    class Archive,
    class Key,
    class T,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void load(
    Archive & ar,
    boost::unordered_multimap<
        Key, T, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::load_unordered_collection<
        Archive,
        boost::unordered_multimap<Key, T, HashFcn, EqualKey, Allocator>,
        boost::serialization::stl::archive_input_unordered_multimap<
            Archive,
            boost::unordered_multimap<Key, T, HashFcn, EqualKey, Allocator>
        >
    >(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<
    class Archive,
    class Key,
    class T,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void serialize(
    Archive & ar,
    boost::unordered_multimap<Key, T, HashFcn, EqualKey, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_BOOST_SERIALIZATION_UNORDERED_MAP_HPP

/* boost_unordered_map.hpp
vew9nWIpX2/F/Rrru1kuh/CciJTePFQh2PuEg64d74LdHUH7nI3+eeSGh8I/crmfhjPWTn47+ztwzrpFcl5XBKd50sgqq3J4v9r+D4M34mxmrp9pzIvR2tlw6brXgeYDSUnuoqamIlyND57u5XlWvEnjVv7SvRRD10CXu9v9e2zxpqO57GbnszcOHbKPnxXuFjxmG9U1RDh3zO7s/mf2L57wqnjoKhWovK+4QplIlQ+z1XHLO99eH3Bux3D7lKX7UMh4ZPzCscvpFaZ9Wb86OFKPRP/c+fXThumcL33PFw5l2iSscEXMrq/45njhVfPkvaAlG/NZP+khgdYYC66vP3YlfWqsM5rTe3au5YKDbxVPz5BFjcSJ0FstuY5yV/bv2JYXebVeaq980iU1w8TrYY9bZh3lMuI5zaKzciUXr+87zDFNZ6gf9MvlhNLHE96hNo7nP3jORCvmLpll1pYVuauI1+kWxsbYGFVhH6c9eH49/JfVm9yumQMtxx8uX/C7uvP3lViGmHvBXFp+c6cYT2J0tp5q5Nl7o4V2c+6VKx+eyzA2GIqO+niwbVTkjlikz40hTWJ3B7t/tdaMOcaWv3HDm+kBo7L4hqbDVWd+lDbjb0lI95i/TuToP9RmvqMv3m6dpve7JdkYDxOvc1Y0o+qH3/6WjX9978zPcxdDbdMsp3ZP8/iqndsXrHXQKu1GmxX/jsjQno/KT2lw17da846xvAmRb9thsEdVu6zUQjeX6QFB5Am3EkmlFkuuvHkyuZQ52+HXwCXtsvtLRlhFVhf5w7aiBUE7/K+/iDeKCOztpelPyU8xkxSb5THoMGAzbc6m4TIWKbnTrR1ldimTNub24BVZoSu3aIsZGrj35N9uN8XfJnWfHd1l0jMmLkU+Kr1/eOeLuwf0tuQYvPuRmjjz82rMXtd7ngfIZZG+Wtj0Z+udZPcc27jZ5vLedbqP6z6cEGRcttlXFNkVyu1iw8Sqfd1l9+P9vrLYyBf1vicrAm8wbK/vHnoXpa8WUaJjL99sL/Xx0gyvBJl+E6vGYZNiDZIlW14nOYznTOy++mMnzmqqLkVEl85evmZ/r31PfYlU4t3g2KLg7Tuyjg7FmuXbJqkP3hjAx7b3y3gcxZjTnbG5SQrwThl0PbjP47e6RUe27/b+MnZfgy7eW4+WXPzWTZ2U6Z3l9B+6Jn7Cbc4g30tKS/NYSOf9VqdL3VHswZMth7meBbBO0Z0Z29HPy7xOhJ65Pm+37Pp7IZIHVU8ES3++L30kTbondU998PDxO6cbdMZO2ub6inbacOcE7bAKW5ffkiT2eoP5NtWHpPpa0rfNcx1Kb/WbtvOGjpnEmWQlvDcZ2jYdu0PXMyPkna5TerFN9/bbB5lLAwXxenwD3RMmPvnleuzGO8Sb1dWef22fkWxycG+jFTnic99Xq7vl/qAx7fttzjrmTzOdeacP78NYeu5/lkbv68j+3l6x2F4mDrd5fyyW99Gs4lg6x51DqgcOqVzR6+i9krWlYUfR8Igky6HXyq4qXqNZSpt/2XSl6Bdt1JlkeVQw2PUl2fPsl0HFueMVPHbXN1wIkZ+zeH+ZvlLItC/62cP0icNzrJ+3jAnpHXJyaunSe3Zz7OCgMp23r97l69eGmK4n5TseFNeziOT88czosYDlz5iqmIKnOlIZRcL18xP6PunvBO4o29wukDRLzMnpYNG+FniskC87XisUl5y6Kzktqq3OibvE5CzDoPBDoezEWh4m977BBfxlUoUAr0LGFnW2o8M/DEO+aTmlC16wlpa7Sfp4LOEl6xm6izLVRf7qjX4jV6UenT+8MWxe5Hfgs8irR5bZ5cRxnCewsROX1Pnqwx5/lZqpOM1gFHw1jvuzkY7zLs0jv9/RZISNfpE+Xxaz9NjXukKsMv5Q3LMmOvyoU6GLTgnb6wa/3JdCc3X7psOH3i+pl7RKf9xc4tdtcZZrouZov8Ilqf7zozf4rjn5BZnmuMjK3Yu60DIqur0jyUlCOmHjmajWOsn+8PR88XtdkT3avHJ7yr2zKq7+pN82qEd7o7cuUqZeuOP+zR7pN/V6t4aFkt9YG29+fcGxUCyX/UxYpHys/kviL0dGm64dto+lWpqPuWwuem1lfl26KOa39cbtn5wo7Derb/fj/HBhxcGe5wcOT36fL1sy8uOuTFQdfRY7kUyp8v/+grDx2HXn1IpNSdUPiveNHl1sU5dkvoM9bRflU6695e3pKfEorgPNrhFZkebRr+QLtpt2yD7b+OL67eTkPV/uYAe1cRTLQfXJ+z/fPAhyulP0pBN/ZicPAyOx++d41X6GWMt++l31N7UVD5Ut90r1bsdftKng3bvkkLjfd7DZUCvnHXtb8GeFCH2ilAqrlMJht3eMCrHm7w817Jrbamp0IqNNJwUz5kd+NmOos6A+JHw/1Wr2pF9lwNamxg61lDP9Nh5Ctebr6J3qRD9dd32y62qcQdtMubP0A6+Abvxw5FTRYSXW5QPpNm/DJIc7phcuCjKdKzxg1JdxWoZZQD+KXYtDdErs1K1HG5J7P+l5q4RmMAyzRFvVyb26+vjDYbPP2Sc1LVVy1Tvpzii+a8aSh490CRW3G7Z6RZ1TOh+g9ObTtzvP8wlx30wrNvXRPftIm624PrmM4cYlHqcFhReRQ6ffzr7f2l+nKNMf3dPQ6ncy7INtuSTfdS1hh9wY2yN2bz8q2i+e0+W1x955IrhxPtbXbmVHz3uc+L44URFs5LJMrHWoh/m8/jq8Zkn+pvQdVW8Ssns6mof0p28l60/SWm7oanLeV9J5rLhTZzifrY0v/ZfBvV9bUidVz3ycKr+4VcXIjSF0LMsgIPtsvWzPIj99THbzxtiXVa+9orS0PNM3O8s1f2ndRCbeCvOnbeZxuJdTcOu5kFP7rSgMbYHDzxGxuQGZyYBT9BYiecwJDpoBAVctTuX97KTJfHnieeib2zMDXNIkunejelrXNfvNPRgaC3ityQIbWrq+mE9apflsXBKZaj9FvKjTzb8sSGP7YUfchpyIxm/ab7euzyh2NUq17i05kyy8szm9/+PE2f5YZt3YIp2PjPm+6f1q1+aya98biRkPZ7K9Txja1OV3IfRiXcn5GY3LY9taXI4dIGsa5gWbrcte/3D67Y4zdrLnM8Ik67y+56unjawflG65mF3WLtGMk4thOzVzIOvWcJnERe5LW1paDVtXDotkY7vDTHqyw539C0cURPNb14ce0DXoOE0mGU5Ou3NZHZaZns30Za/myKr93HfOU8XOTHyceE/Wopu1g6Rep0ezh8NYaxd3vEm/3uKia11yj+LbVlMDjm9sL4Q11Gwj6Sj7goafiuyxl098vZmm9tPgjneyz/gj3G2fSX5KvHPvx4EjQkWJIzsZG9OSZNXlpM969WulzvArHj0ad6P/s4e/jzRXn6h7p4ai6Z3A13o3NqQrmTcPD7ROePvIL0zF+Gq8jjFo/jHQPOGVW3VZ0dhPTDXRrvnXy2X22kONaRd2fY64y5UaZ9a0i8YoIM3EKHurfKf6JkKGbLU1I0F9RkqR4rn4Y+bN6N0e1af+rpTelbJlf2KOfdAdgTmJ2px7p1+Pr993uLz5e8tYQsI33kgO+jLF29ause0yVh/Lx1xDihS1U07nF905ynE6YmRwSvsMdke6/6L2Aa7BMWIGvZTEfoWGE6Ur788Xe065E72I3jX7Y8cTP/prN/RVPLzal2JpF22uc4Gf88JE81u226EcW4zmX4YXx6X06ETUH1jafXvQVfXpnfMDOizHMl+43Y4IO1vAk9U+iWmc7Fqv9Pjrh+5S9o4Xj64+LLD6HmqtblTltzPR7fOOR5++C9SdJxtJKtw7QqQ/uuPe5cOufcz5XfrrHry8rtLjFX2NPXpE6C5nxwsD944PYzq/Rym+t383qdz49qxb6rJaBF8LLX+8Ynip627mwa8j5zXvRDBJ7m6IaaVcPYyP5Jn3o1vx/7y+N/P5su6t6ZM3Yp97/6r5qbG8sq58mVitYl3A0L1dTkFsl4Lkrl2Prpo9Ounh4RFiO/dNaO4b81sbbjFvg0hmyc02oUzW9EavV06e7yusrFi8u9NZlft84fL6Rd5an1Qv944mXK3l0q/7REfP0ocKk2kiKWW9RilH6z9/snzOuHJg6mmPx7LB2Oemz4Kn69mSFs9NpKoV0N4uyl5SGBssS02uOGEwc3h2uU1YbrhXd7l18r2ig+oLF/8DU0PP5Sef02W/G2snXRwQPVZuQjjtYJT1vHpbJ5/Q4y9HLHQV3WI/njX92dJ/jM1WWeX3ik/6pE37L5H+ZPcBj5Y3bwWau8SnvS98Llg329RSrlSuRZnYzuAgd7vwQTW2yWCCbaX8XnBfbjBttfNsxGRpW571cMy19Im4JaPcpYyiaylRwxV6nEce9j57l9XRSTI3Y59/N1jTdvutp8EGSvnBAq7Kc+VPHGYHfeb99k9lWDd9eGe3aTDJ+xRJZq7lqgj22rvHm3BN55845syfas1vuhF08/aiqcCTZjaVUeu4b3qHNAc5t7x/ElbQPt+6nfF3jarrUcYsR3+JD9W4mWcDrkr3HnjWLA69HqH/pKOwa/Qm7eT13Vbe8g/92yiu00yn/RNPCs1xGe3dLZs3x9R18vvj9OfnV7reHI2Mvsc7bmguwLtucnynn/8Kz/mnlSs/jk50n//x+FoH7fZ+nYlLg0t+7qYpRxcPse/cdcpf1+/aN9yFc4ZcNbzbsH2XdlbmOBA6mpTXx01Y+wT6UU74qCypLHmUO8XM/8xxqtNe/n60ZOTFUmd09d6Nez9UVAYf3hJbLnzx3HvK5Dm930d7fSrDZuP3vjIbsFCdjby9uKLP2XuV9VxuB7NrQUfB7/qkOgPx3X58hj7fWhTTzxfk4PstfnFtuUIzybaw21Xe3yHOY/KZl+uU45lDTcUbSFYjvmZp/WW3lm/bCJYJklR2/ii4+fjd1dSAA5t1gz9/9vp6tL/7ldvE51KbEw3hL0n7KRb+Rm/qTnnz+fvM6AzcSRfTkhfCFxuSslqv2awPzXg6//Ns3+6Ygg242uWmLVydTq0lS045zppS/BcuXIo6Y6xLeR68zGHKacXvEB20aWVXpIaIYD3l/Kukq/1P+hq/Dr8tNRxItj4Qh/3lODude0p1+cyG12/2OQiVLXmYj6XwXDtUbJB8qmbOT/dkyRz7bx3D20Hbs5e9rAeChusOn//VnX5mMeNL6IUbgh0qcqWNs10ij3sebHhDH3slv2B2Mv/z/UO+iR8sFjdWBQnUaokszdN+ogwwxm6dpNhsuLoUuW/TaGjdM37be9Yhlm8Lzi/W2N71zfZt+pDgNnFXXkk5i0/p9LucnVLLBYd/RR6wlPFdzDEIEuBtefrM6MNTlgrXrmbrJOXWcz/O/+5Jnj+07Ki36+7bgpqqtM33F83t+l3tzr/OrzONv+Z2Zsslpcal98tqAn795MSSniVvh2Ypl7f5sdd+PPFUelfpNz0aZGFhP3hHVdOJUyPrbs4TTV+V3rDvdqcPLB43+vk8O5POM0GrvXQ9LwUfn82W825ihjmBYrAw0WUjeX2+Mt21ou9+E6l/4Zba9NIkpS39wrvA4JX5A+eimea+KzzXmtVeSnQ7nFt5oPks3bLBaW7eLdN9gA3zyR/GMj6cv88svBJEObN78Xza1PiOFf/vKa/6SvoCxSjPBz+EKlJOuZ2fuTcdeKPC3uMCZdy2YGy+pPflPf8LVk8Ww0/nLFhYndL9tXlSdMH6xK8RqQedvwlKF6Y/zSz2uI45jIh6DHe9Ga6rv6RlLdST5/llKlpE/mh5eebZ5sK7SqpPji1cvZoRWV7qc3hwUWw4oyKivjB0lvF8ufUDvEfxIoe4lEvBk9yjrWFYocPeTwp6CMfmHxTUzYfabdj7oNZmzOyS7U82gQTZC3t6R0P9ycVs51THXnx81BBaWNJRYjY59l61yMOr/cPI2WM/dBUrpC6JO5Cf/LiWmJvsGa/adelbY+1OybtZxZO9jT6nP+9bMXzxbKv9ZCSXwfk8f+4EHrMXlxta2/KvJVxTubdl/1yTzGTnvRA752t3VN1em0hJ1vpsOOvDPaUdKri8RcyZEmJBYXz8QITrV+V00IbTBrZf7G7HtN+eXFASvZFa+SLxVvORFT83rNE31Yq2oKAXn13LPSwn+q+WFIndPtutyapsfnnTlmU33f499u6JJRs314Tu9L/QKY0TN530MXH2vC10RExr36SQzy+zez1X48NdWrJy2rsLLMa/qZtd059nVJDzIth5X+w4Qz9rV/7yXbIfVxCpS1uy7WSFuVHe6+80nvwcpEt6Kl7+gW2/voc+H7Bjt5k6/oQydevM67g7v12dTEZbP/ntdxXpdFL007bruxHyI26zbeojcdUlqYN+SrdHj426dWtzU/zeLXPkaCs75yTQxT7REfF3f3TIV4TuRGwmF5dHC82l3z2jm5jeXF3suXvT5vtcFN3Biy9+EJ3aX1087+g9KF9500b64PmxduEdQaYalTFWPUvTG/iMKSxOl77e/r68wLJVPo6Fj6Hbcjkz/NcbldNixel1b9evfNOuX/fA87RuyMzP7YoXhzheu4a8jeAnfmt5YXHmS4Pb0X46E7yH0JVdNvUPu+/rd59QPuU6X9a6cqRERvDpqav1Ga239wSpEDLT5n9vP7An6JyftXOFw0sF64hp9uj37EL+mw5H9auUx4pLZnEW7sniP1t0W43zlofc9TvarYrxultOjtmHJPobeSlUXpXcnvg1SZ9/85lxvSw3XP7uJeXsGBb5rKotZfw/BPR6D10Yy3woImRw+M3Nw7TEkrPs+Zea7ny4bdrTd8H3QNI5Mcc0+c6jqgeibY1U+8VHcW8vOd2+cefcnZMPDQ2unnX/frE0K9Tqa9KVLQ8DI5YDnsn0nP4d+SFQpuTbEo94UnC3RHS61NWrzQNFQtUugY+HXck/HrInGWC3+xXf2VIdUBW4QHNS9Di75H4eydOGEuOPLu6fwU2M2rI8lb/h6nx548yFOSWvU3sEP+wOkjwWV38zMX3w7dudSz+KJbeF93xufZqYd41vlssuSMjJx3O9cf7xTpPStKXqkoBHNVE1e02ENrb8fpWl/WlR8UbF3s8BjxauT8xf/JDqPKtAefs78Qm99LUf68tSbTV8vOkHpU63W+beL2gQmN3tRDPymfvTZJggN537wfkr0cPzHQdwk2LpObwTov3sx4Sr68056ThiSYvsnHQZtDs05OQH3CbMf2OiGtjSj4yqfjkpLe9oon2f/fTr24dF8jd1NwwdC3qb17Ev3/Vw2Q8dD9lilmZpTwP7/bLFJd9i3z+QK6rsiX+XzD8Z7BlK4625/N3R8oLn4/FTbHl5PH4p620TfMotB9c1Fbfqpu3kur+c421Hebzn/Ysk9YQAPvWrpXWuyx9Fh/c3/hxqVx2MOUVktdb8pKgVTyTTMDWsNytk+rVeT5a/YFjvzVe1Ee8WS+n4R6w/eu8fy/NyIubmWx4RZTASbtM28zmkVDn2hKHTVF6p+/2UX09C442BR1pHT99dYE/cKJfK8eiBXpjgem7GtmYavkPb1j+yr3KpanP7FtOScpxVIPp0nCBzivjxq9LsIrqc
*/