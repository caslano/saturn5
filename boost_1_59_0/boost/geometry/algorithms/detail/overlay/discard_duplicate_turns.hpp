// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2021 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DISCARD_DUPLICATE_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DISCARD_DUPLICATE_TURNS_HPP

#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_ring.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


inline bool same_multi_and_ring_id(segment_identifier const& first,
                                   segment_identifier const& second)
{
    return first.ring_index == second.ring_index
        && first.multi_index == second.multi_index;
}

template <typename Geometry0, typename Geometry1>
inline bool is_consecutive(segment_identifier const& first,
                           segment_identifier const& second,
                           Geometry0 const& geometry0,
                           Geometry1 const& geometry1)
{
    if (first.source_index == second.source_index
        && first.ring_index == second.ring_index
        && first.multi_index == second.multi_index)
    {
        // If the segment distance is 1, there are no segments in between
        // and the segments are consecutive.
        signed_size_type const sd = first.source_index == 0
                        ? segment_distance(geometry0, first, second)
                        : segment_distance(geometry1, first, second);
        return sd <= 1;
    }
    return false;
}

// Returns true if two turns correspond to each other in the sense that one has
// "method_start" and the other has "method_touch" or "method_interior" at that
// same point (but with next segment)
template <typename Turn, typename Geometry0, typename Geometry1>
inline bool corresponding_turn(Turn const& turn, Turn const& start_turn,
                               Geometry0 const& geometry0,
                               Geometry1 const& geometry1)
{
    std::size_t count = 0;
    for (std::size_t i = 0; i < 2; i++)
    {
        for (std::size_t j = 0; j < 2; j++)
        {
            if (same_multi_and_ring_id(turn.operations[i].seg_id,
                                       start_turn.operations[j].seg_id))
            {
                // Verify if all operations are consecutive
                if (is_consecutive(turn.operations[i].seg_id,
                                   start_turn.operations[j].seg_id,
                                   geometry0, geometry1)
                    && is_consecutive(turn.operations[1 - i].seg_id,
                                      start_turn.operations[1 - j].seg_id,
                                      geometry0, geometry1))

                {
                    count++;
                }
            }
        }
    }
    // An intersection is located on exactly two rings
    // The corresponding turn, if any, should be located on the same two rings.
    return count == 2;
}

template <typename Turns, typename Geometry0, typename Geometry1>
inline void discard_duplicate_start_turns(Turns& turns,
                                          Geometry0 const& geometry0,
                                          Geometry1 const& geometry1)
{
    // Start turns are generated, in case the previous turn is missed.
    // But often it is not missed, and then it should be deleted.
    // This is how it can be
    // (in float, collinear, points far apart due to floating point precision)
    //   [m, i s:0, v:6 1/1 (1) // u s:1, v:5  pnt (2.54044, 3.12623)]
    //   [s, i s:0, v:7 0/1 (0) // u s:1, v:5  pnt (2.70711, 3.29289)]

    using multi_and_ring_id_type = std::pair<signed_size_type, signed_size_type>;

    auto adapt_id = [](segment_identifier const& seg_id)
    {
        return multi_and_ring_id_type{seg_id.multi_index, seg_id.ring_index};
    };

    // 1 Build map of start turns (multi/ring-id -> turn indices)
    std::map<multi_and_ring_id_type, std::vector<std::size_t>> start_turns_per_segment;
    std::size_t index = 0;
    for (auto const& turn : turns)
    {
        if (turn.method == method_start)
        {
            for (const auto& op : turn.operations)
            {
                start_turns_per_segment[adapt_id(op.seg_id)].push_back(index);
            }
        }
        index++;
    }

    // 2: Verify all other turns if they are present in the map, and if so,
    //    if they have the other turns as corresponding
    for (auto const& turn : turns)
    {
        // Any turn which "crosses" does not have a corresponding turn.
        // Also avoid comparing "start" with itself.
        if (turn.method != method_crosses && turn.method != method_start)
        {
            for (const auto& op : turn.operations)
            {
                auto it = start_turns_per_segment.find(adapt_id(op.seg_id));
                if (it != start_turns_per_segment.end())
                {
                    for (std::size_t const& i : it->second)
                    {
                        if (corresponding_turn(turn, turns[i],
                                               geometry0, geometry1))
                        {
                            turns[i].discarded = true;
                        }
                    }
                }
            }
        }
        index++;
    }
}


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DISCARD_DUPLICATE_TURNS_HPP

/* discard_duplicate_turns.hpp
WDFuFDa1eFH2bwwAASM4MG6dtPJlxfQmY0PCTDFC9GInZOGC/Xk7gGlUBAAK009oF68uhT3ikFbSjlreYtSi4rgDr9GMFsgthCUucRBxM38jCm8dPcLcYhc6Op7uQOqpChVaDdAF5G3YzSWEno6NRSzLhjSHHNehg7V40ZwX6lrOkd58HR0JA/xHkZLJDMWLCn/YxKkuM9mioP0JRmOH/YC7oIO9Wt4vk3kOgglojXqHGkX6tTpozmZsztartOaYyYSmhYrpwvAeQ2n87gsL9aPfcFGhIZB0N8dRjXkbnhtouvKiiSgSYbYyMkXKOHELwrQC0c4BE9IV1mMdBNOCQKOdfN0VpO70FpsyFlhrpSpCQD/8sv+YElKw2ntnwhhlwpVaoy0amt0yzLn5SlptcfgSCtigQB575jxuYAJXVB76yxUTRAOu2fe1niJwOiydKuFSftVXy+voCEEkg/RF/LrfqqSxHkjI7U2HtI6sDJRGE35i2YVa4NVq7yKK8PHmFdS6hdnW5bNT4wle3qPsPaESfmUVX12YQDqDMA5EPvyq9KZ+RM1ANU+PRSBvEuTFbsKJKrqIV0f2LVvZ8+M17cKj4zkilb3lBayC1nLrsWS+NMdxY8YszXHBaYi69O5UtwlOD8y+AVUdIv8xJeYC5KziH54NXZIVM031dOMHaYAnLitQvlHgkiaz+VdwIJk071sOxEUZ0qcc//47h2V+RqvnkY0f1BYxZMsUGEO21PecFsSWIBs3ZPJTSAoS3NZZqL2wqdG4ydyYNyrVdSYQcmJoZUJlhVN5sBMDaVnk1UgfwhnhkoVRFBSJe+Sjmz/bdb627vI2KLD5C2GyF7J18cOyuiIhESnVRvZCNhFBNOOQGGcPZRNNFCo3jRBlgjfMFmdzEF8Hbb7r2S1xAuvHRKQsy9VTl90AGZkJUa4tKh7cDfZwyojLhC7gHCR/xpH8b5ULvwBj/N8gbcieMemjC11qcmcpF3vrCb0++5BGlj49mt/lfyb5qJObJba+q9xJie9wM1O2YHG/jD1SYm7i7YrzOQnTtBRpIDiFAh1XE/5BpQpfqwvF2LtaqTnVuZpW0B/1ATKTPXpyIvk68EzCrYnGGDtwd7+sjyug0FgpusmNEcKoR8eUpCUcA549nCWspgTh0jg/inQ9Rr0i95WYbjrWtg5LXg210/juJV/NFcLKV0gpp37od+uHfqs29OcX8qF/PWfof4VvQ6OdqrRMqT7oaXK0fvQE1zADjtgb9+qjGgP5UsK3EREdnTi9ggWNkuMobYgx4S7UMPH9nS9thynvTlwRjumYQY7+PnsyjOyLaISjl53AkN7xbXm4ANFDKdZn9UNanjU3HxQjL5wFmG3ykLQp5I7F113eSUj3FBVv2gDB5+ydOxctBl/XzGzVGfi5UTcDz2gc+3Oj+AysJHtBJ9l9LNM+1saY3pQxriXz7R62aupRVN5aAy+Qa335YAD+2trgRpSHobGmQvUnjPYWE1lqr6N/UbjVe5qDFqOBJ5r3e/AIwQmE5wZu/btIQ31/4hItQIwnzD48V4G3g0+LEYAG2WT4v4zM6ZFIS/PIOvg/R7Br8FZI+RFammRUSVTTSIkD1RdnrOT2AFd88GTS4pfh7iHXZ8Q8ilGl5PuMq8aQnXakepRIRXBGD3CDRUctu/5cYrvrZRWenQ7Hi2+Dw/FaeQ1p+9asybFYf+Qa3KpYc4zH1LNp7BDlr3+Etmo412KwDM7MKz/nZ2ZuvEhHqvNFA7fp66SYOMI50goLty0KUxDb2ZMRddWZuzA1WzFU3Nvbr8U2coWrveUKbel8awRfOucZczTnA4rm3JgaMCVL97CwXt3LruhH117WJpAu2KjoP8N4wp1J9Mu9eIGjmvt2ruZW9clcy84+7aOvqwRNP2pMGHPUyWg6v4WXuoj/xgKtDI8ANQqSw+xH8GMZHzYhp3nt+GliAn9ZgS9s7xKgV/sSlVGRByyKwZd0TkRJe8imw3viG9GXkJpi1+LLXVFSQLIr8DfC2HYH1OaH2hKOl0jPRAkXYYKTKuEJZ2HCGKqIJxgwYSxVxhM+/VSWN1Bc5G0voRKAZSZquqsxqApHK6t7J6JYL1fKDyfHS2h4wVb88hNZckibgQBhSXhmL0yT5SEhRF9CdxA2B/MfGDYfrTHYJF1dl2HZ2iFlOfgsAhAlrXgBneCCJRKNOWthAUbZ+FbVD0LhuVt/pL8sWrTLoj+fJA1LA3RRJO8KPEgy8DvgqujBz3MuC7woRiqyQJdoVLCGbfBEmkbzcEGpG9Sg1EppNzxx9FmPaNQ70X9NYYsqKW2+kXfExzsymQP5aXJpf1cYvfBKUAj6vioE3TFECHqXH1bVWFU0l5WSrFlCd87ga9w5pMnjJJ2U5MUcKclTQ6Qka7Iei4r+J0kBzKoVQ7P2A2Z1fiJ5/DzYhqfAzDJpWml6SSkPBifVwuGYvscCnyxLLzaKCv94D4oJiAEkL0b0K2wUFW7lHmOqyyJyfkPkrLY0bTKw9xg0i/OSSoPh7Tn+9iJnAtAjFcP4oehAkQIUkJ8FVPdOjlNiNQt5OE9CXjvSdiadU5jFB11GvhTOaHQTZ5CNgSXFGDBwIXRMGC2vOUhHOC63jE1es5ve9uUc6N1XE1Coxy9j7MMrofLA/Q32lh5OAvooTixMuRkumMC0Onv6VRLmoLgFN4hUQNbcibzaKIZpoctw9WI6bnlwWLSSkpeiJLuMw375t5B4p8YlCIipfLc0bRHthMDM4uS3CepEC/1khAZNGE3sZ4M0zSKVW6WVP8WpW/4y/rszBXs1X3ryFa4e8ap+If5jwIuGhYukmXWp7rwMKv/CGHKgN47+TNMWZh6WHkRFZOYJ6Q/ABGJ00YXUBLo1l+N6MlZ4FwWSLgGTSqD7voxJeptCMQwEtzfnwxfxzJghBS5Dl5JpVgwuher2sXFcQ9CqRWqEKZRYQJ9mFHJod8WIjPgkHowz1eQy8EgcUE+q8Si8FHAzEleY/foPR2T155T+lnWUdzxd9DY6eUnIJlYaFdvBnSeKumnKYPoeQL+hMjXSCFLY5Rw4eqpWWi7qgdIVUHoylZ5sFrxlZsTUFTimbhB48gceCFZ7Sx74Pl8tGAlwZpyf9Cw5qtCgzXKjQ42pjXIDXXwjKNhayvF/FSxKBc3+m6MUoEWEFyiH+fKgwjYcuL+EMFCMsSi7CjoPnFyn4mVZpe4c1ngzECsEm0gKDbRvro2y7oeJgVszJBTbU5yB+3E/J0ac/9lxOY+fKycMdFzO+oLjkpOW7oQRxTuj5bW0Kdcqm3Ito7dDOZuy+Eo4Qc8dVqX3xo++UtQciaDCbkU3atdjQEmyD0bwKOE1ThTL17gw7jjFAe9zaLHEnezKs3Rxwy88S6elcZ6lCzlecBYPk7piBNfNDVKoIvjeIXeqcTIe00JderFNiVG2ohtNTlBHhU2aNgI1RShRxDBl0jZakTvlmBLdD5Z7HbQtpiA2P+rgaqJC+CpzObZrTCmZnTulSZPpwSGOwQfUmrHMaqNBnMTRTYe7YVKHivUIpYqNcozs55Rrw82u74HdhlC6BAykCKouw1DcpArisZKBgfsA96wgqCviYr4i/nHmMHcAWgac0IMvK9f9WdKDB8lsnF/7kMdDC7ecx+VMatCVD6QHufeCAnA+6+pCQw6OaSoGi/5sJaiaUujyqxEYCotFKIk2XxJFr95a9gz2ptpbykOkvXT4i1b/v6EL192ye9BUwN5+uUZw950+zJUO/NByhtlVrtMyYm4hNNluWI/mAgUiwCks45YRqdttNDj5UuqggQdbJmkzu2u8ghWOrLKGzfgsjgxXg8GCmFTCYw1OXr50jLS5u9e6/MTypaO6GSZY/McyeRvgzDeoSkUau+lRGLulOdq9cO5PoGQgZOMu6W4ubTV1kNKeewQP3uDliuFFGsGo17YMoYfmXw5X7CQK3rgpM16/q7mjFW7rvsZhrRVcgw34S0knVyLtQVW8WUN3z7XK75DDLlh9RdniW3VxBQYXZk13yDIRjyW5mlIksQ3koRGDqQ6dEvJT9zsNyfOzOJ1qRR0d4Q727ApSEEozna1bhIulW+pb9wrnHw+RFC05RhnqhAGBt1AcH47I75GiMhfBZIjusYPt+Da2bzjhxNc6rG/la7T6JG3Nui88rJ3qYe1IjubTyacXD2tiidfmssQP+Pplwk7O+BQZC3nPKR1xpPFO0rlLfEMY9gAv/s86t5R37u7PqXPxQZ0DTsG/C+hSnzTVF3xbOD+wGsXnwtjZs9k/f/aJHOZd4t3LOCH1fZ7aSKnL1O7qJUvipV94RaWmDkvnDxM4hVaWvf1FjYP6zQl+gLTzsAtAU0hTiP0k2hEujJC7tat5DPBJsBdc5m70JMDr5A9FGGPC07oF8kKOmHlzhByRSIDwalEhYa41j5VCzhhdavhZUcgbZo9Qno/yXLEw+leEfMp3S7FOBfs7czFsoLRib6CbXR13U9Co7CLf/0ksmTVW2amNxo8H+Gi8xSVreuMoZbmWISu2WWXF3uVHT0l2bf71YnQDs1GQB4eUJIyMgaL+1GGztOm7XSOJ/gPqb4DcFFF1gegfyyhsJdlijaSIR+Tnx2MUIRYiXlPlYXT4Y7PRmGOt6gvGcf3dPBDINZBlPkPY+f9vOG7wvvuGlUD+hxSZovP/9nHaB9O/hIEdPGq6A/vXXhw1t1RYx53nhl/mR5Z+9TKnDmy6/t+YfnSspBsHQ6JWdcg43BV0i7sQP1yorRKqgFLJEbBn14ASEMkmT3JylZmuNx9N1EXwtUlbMwFuPYRWROUUyCthiAyZH3k1WqxIzy7nc4ugEa7aMHvHR/CTw0yccown8uR7LIztl+WN/6eJhEutxsZpBfIPcobNx1iv/bRshglQSA+gLfJNYsjZPIPP9vf/RbMd/ILZVq9nnOzdhsGT3XXR8NKKq78z7DmtX59SpBh+Mhpr3ZUcnwu6xW/EtxcjtJt0T33rMWFC9gKssUUwvpDb/nj31EjCFJ4tfzAY+EtdzhfxDj51lDroxA4aDh48iLDgPYbf/e53hsxYqbCax28QrYi5VEiMl1Uzu9H5cPp5ZTN5ZRcr7KcanWpMZ9sPf2GYv7FzwyPfwz9T7u+HPxRnWQ+BK0W8ap/H6e5q3uHTC6HDbg5Cqbvxk45owpgYibgsuns89ToJbAWHNBVhgkckJoTZmr2wbkiktTGHn0FrLWq91M+kI4RBPCFNiA5ZEs6RNQrKXMFt2NH+8FJH1v7wvqH2h2XVh2VpPdIoUYorLG1nBy7mnE0OTxWV7vH4d8WCnyXHctlg1sn12wug16V+eTp69VoS5kxBYI5LIC//GfXBPwjnwrwE39ZgXGbDlzGgf6I4GnP/4xNPEdklPzv8VSK7ZeomaBxy4r1xwfCb4PaHv3oTZMX1ZJv2E+8w8vqvbWb7unYJPtfPL8Gfa5fgEPr7K47zD8+n4zzV+RgpGG4GMsBM9L1iq+syhxwKqf90x84TRW+nI4cShlQ33oK+nQPpqlMJVNpijeRo3WUiyAgzHyuOpcCt9Xgc++GvC3nVV1L4QyJta2SSlHTHVEs4m739c210mvv46KBiWtrEnrkEAaaFSim1TuE5rdKzmJcxSbtrKe7KOC59cuRY0UGODT3LaUtcPOOw3PsbFJR0BQg2L7kkQFB6ye/KSz3SFIS6EblNEGn2kDWS/xRmi/46ilitCMEEo3ILFVKQMRMypKWopgKyIhKlbFJTmVU2yK1EJ6eLhyQj31C4wwHZ3joVBXfPInfYWwaPmk7Lk12oOyUaXSUG+NsfcQbXlaMUABo4sJr64wispv5YA6vDBbAknIMX8f4LB4f6I+7LS0e8D7kvN3JfnlyERR9swIu+3Eb1A5XX0gvq5/VuuFeW9e+7ct75BrJe8h9JxWH1JFEq7tJcsNudFnUZXXOYLyOTBd10iqWnurjPeYW3FAV9nmMpNyQYBUWXXcwP3hE9IYxWaciYxSaHIsLEqDNqaTOciVrUmaSlVRaUIDQYtHMk0pf0dV5qkddtkFKdSsjBZRx+JAXUkVlqwDDYzT9QBJ51uEdhg86UO6ArddLmxKKdJ+qLulMDI5vMiZH1YcX5pm4WqcQao+zGWRRJFfn/CkXvW+XfEongASyu8r6rC5reyJmbeAd7ZXy/Jm0kUSesGDggkiOJz+v9p0n18vEfq4ymMqYYWZw0eMvYuBGk/nVSIHRxHRmjsegxG+Kr9fA4VxXB7ck89sDcAgNh+yzzlkh1FKGv3JC+yQgzswjaiCiGQmqTOT3zdHq6nHrbhIoJhMiBNpM+YqYM8xgnnUQd6SSWc/O/lVzfsIorGlbzN70u4jm9dSeGDVYUEBig787wJm7BZspqIMrZxoJCCkHOI/VtYyNO2nIilKERGkpf4VscMbjjUE/iIfSE15GxzJyL5nTScrS8lM5SgksS1AAMLPPTzYBEqsGULCdH42w9V0Oz5UIPaYzlaxAmppochuQoKiH9N0FhrCA2dWSiMSYdZwn4Ao2ncT7ViaziE9kI/I+LtBvOBPpXRz63GaQpaKxGnY2TyOdPcMghUh058gPPb295jbvueOytv+ZKEFR++FSIRK95I3JNJ3YOkI0pTJ0zXff+Iml8cHeTeVrGOFMcr6TFIW0PT1PNP63i+GX/SwhupFZHTppM2z7OJwF4KUbB4waMFnbhUZtB304MOQydGAnJ6kDD96WIUEfG8ndPOywrZf5+BDpKAielJJreTFbnmoWmHdbL0lELVU1VFEOGtClDCD3At0Vj7NfIpH2JHH3un/lBqyD4JGyd+4/ua2R7j2IQPxu6jcQnH32tUazpYxUfFCpQgeQL+CDabfr3okPgf8NTc4X0FiG4Xh94YSWp8Z+l+75PQaarYQljLXs9r9DAkTrEeaeY/JlNhS0UQ32EZHhZFHZVfiIPD5li9ERo3Wt/vAtW4t9S2+VYLItJgJg0mpoXSTmU/p2iwEB9MII/hapR4Pwc/BWbTsHP94QYjZH1BhijHnL8Zwegm8Pwe/8GWswJlXq7jZ+/rzGi3uZoIVilcUCJalFY0YzrG9wnxaYcYg48xJAqQe6vWglJrLOp6h2jSqUQaBrqAkLV9NBwiC9D7fMf13egfHhDnyyptkIT//b/g98id5NPjS85MhDy/tjHI4fVc32QUwtn6v7ycKYlWjjTYlJfqeFMS0n6sQVxF+DMDdT4kksDNV4hH64PoxaQ1BOm3cRuDXxVfFMMD14tBJX4piXsl0VqfNPt2fimaA9arcQ3FaFA71ryGiCXt7QS57SEuc1qnFMvxjltMLL5fTYtzqmb7++tbNlxG8U5rYLnN+A5J85pCcU5nQvJvESMPcWf0QbVDtVBxfUGFWaUFuR91x+WFfGUA2mTrcMLeb8j0tyHvyQcaiQbOEIMnQosqRBuVJfpVD7Bjr/TMvUnjFEdvMc0RPcvk2pOBbdpYS8ovgLZtchLKuQdmXNz5Lqqs8rSh4gaGsRqqe2QllTEuLsKUCKhgeBxoUZtTwVvz/K/UXu+Kd1SH/xIiASavBiQY25mBPDXTR7kr6XQqWCPxnrFsFWRhAV4r/cUOCiHSqkpDRzo4M1j96lt836Z9khHoTuyFDrX
*/