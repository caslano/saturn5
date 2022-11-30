// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

#ifndef BOOST_RELAXED_HEAP_HEADER
#define BOOST_RELAXED_HEAP_HEADER

#include <boost/config/header_deprecated.hpp>
BOOST_HEADER_DEPRECATED("the standard heap functions")

#include <functional>
#include <boost/property_map/property_map.hpp>
#include <boost/optional.hpp>
#include <vector>
#include <climits> // for CHAR_BIT
#include <boost/none.hpp>

#ifdef BOOST_RELAXED_HEAP_DEBUG
#include <iostream>
#endif // BOOST_RELAXED_HEAP_DEBUG

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable : 4355) // complaint about using 'this' to
#endif // initialize a member

namespace boost
{

template < typename IndexedType, typename Compare = std::less< IndexedType >,
    typename ID = identity_property_map >
class relaxed_heap
{
    struct group;

    typedef relaxed_heap self_type;
    typedef std::size_t rank_type;

public:
    typedef IndexedType value_type;
    typedef rank_type size_type;

private:
    /**
     * The kind of key that a group has. The actual values are discussed
     * in-depth in the documentation of the @c kind field of the @c group
     * structure. Note that the order of the enumerators *IS* important
     * and must not be changed.
     */
    enum group_key_kind
    {
        smallest_key,
        stored_key,
        largest_key
    };

    struct group
    {
        explicit group(group_key_kind kind = largest_key)
        : kind(kind), parent(this), rank(0)
        {
        }

        /** The value associated with this group. This value is only valid
         *  when @c kind!=largest_key (which indicates a deleted
         *  element). Note that the use of boost::optional increases the
         *  memory requirements slightly but does not result in extraneous
         *  memory allocations or deallocations. The optional could be
         *  eliminated when @c value_type is a model of
         *  DefaultConstructible.
         */
        ::boost::optional< value_type > value;

        /**
         * The kind of key stored at this group. This may be @c
         * smallest_key, which indicates that the key is infinitely small;
         * @c largest_key, which indicates that the key is infinitely
         * large; or @c stored_key, which means that the key is unknown,
         * but its relationship to other keys can be determined via the
         * comparison function object.
         */
        group_key_kind kind;

        /// The parent of this group. Will only be NULL for the dummy root group
        group* parent;

        /// The rank of this group. Equivalent to the number of children in
        /// the group.
        rank_type rank;

        /** The children of this group. For the dummy root group, these are
         * the roots. This is an array of length log n containing pointers
         * to the child groups.
         */
        group** children;
    };

    size_type log_base_2(size_type n) // log2 is a macro on some platforms
    {
        size_type leading_zeroes = 0;
        do
        {
            size_type next = n << 1;
            if (n == (next >> 1))
            {
                ++leading_zeroes;
                n = next;
            }
            else
            {
                break;
            }
        } while (true);
        return sizeof(size_type) * CHAR_BIT - leading_zeroes - 1;
    }

public:
    relaxed_heap(
        size_type n, const Compare& compare = Compare(), const ID& id = ID())
    : compare(compare), id(id), root(smallest_key), groups(n), smallest_value(0)
    {
        if (n == 0)
        {
            root.children = new group*[1];
            return;
        }

        log_n = log_base_2(n);
        if (log_n == 0)
            log_n = 1;
        size_type g = n / log_n;
        if (n % log_n > 0)
            ++g;
        size_type log_g = log_base_2(g);
        size_type r = log_g;

        // Reserve an appropriate amount of space for data structures, so
        // that we do not need to expand them.
        index_to_group.resize(g);
        A.resize(r + 1, 0);
        root.rank = r + 1;
        root.children = new group*[(log_g + 1) * (g + 1)];
        for (rank_type i = 0; i < r + 1; ++i)
            root.children[i] = 0;

        // Build initial heap
        size_type idx = 0;
        while (idx < g)
        {
            root.children[r] = &index_to_group[idx];
            idx = build_tree(root, idx, r, log_g + 1);
            if (idx != g)
                r = static_cast< size_type >(log_base_2(g - idx));
        }
    }

    ~relaxed_heap() { delete[] root.children; }

    void push(const value_type& x)
    {
        groups[get(id, x)] = x;
        update(x);
    }

    void update(const value_type& x)
    {
        group* a = &index_to_group[get(id, x) / log_n];
        if (!a->value || *a->value == x || compare(x, *a->value))
        {
            if (a != smallest_value)
                smallest_value = 0;
            a->kind = stored_key;
            a->value = x;
            promote(a);
        }
    }

    void remove(const value_type& x)
    {
        group* a = &index_to_group[get(id, x) / log_n];
        assert(groups[get(id, x)]);
        a->value = x;
        a->kind = smallest_key;
        promote(a);
        smallest_value = a;
        pop();
    }

    value_type& top()
    {
        find_smallest();
        assert(smallest_value->value != none);
        return *smallest_value->value;
    }

    const value_type& top() const
    {
        find_smallest();
        assert(smallest_value->value != none);
        return *smallest_value->value;
    }

    bool empty() const
    {
        find_smallest();
        return !smallest_value || (smallest_value->kind == largest_key);
    }

    bool contains(const value_type& x) const
    {
        return static_cast< bool >(groups[get(id, x)]);
    }

    void pop()
    {
        // Fill in smallest_value. This is the group x.
        find_smallest();
        group* x = smallest_value;
        smallest_value = 0;

        // Make x a leaf, giving it the smallest value within its group
        rank_type r = x->rank;
        group* p = x->parent;
        {
            assert(x->value != none);

            // Find x's group
            size_type start = get(id, *x->value) - get(id, *x->value) % log_n;
            size_type end = start + log_n;
            if (end > groups.size())
                end = groups.size();

            // Remove the smallest value from the group, and find the new
            // smallest value.
            groups[get(id, *x->value)].reset();
            x->value.reset();
            x->kind = largest_key;
            for (size_type i = start; i < end; ++i)
            {
                if (groups[i] && (!x->value || compare(*groups[i], *x->value)))
                {
                    x->kind = stored_key;
                    x->value = groups[i];
                }
            }
        }
        x->rank = 0;

        // Combine prior children of x with x
        group* y = x;
        for (size_type c = 0; c < r; ++c)
        {
            group* child = x->children[c];
            if (A[c] == child)
                A[c] = 0;
            y = combine(y, child);
        }

        // If we got back something other than x, let y take x's place
        if (y != x)
        {
            y->parent = p;
            p->children[r] = y;

            assert(r == y->rank);
            if (A[y->rank] == x)
                A[y->rank] = do_compare(y, p) ? y : 0;
        }
    }

#ifdef BOOST_RELAXED_HEAP_DEBUG
    /*************************************************************************
     * Debugging support                                                     *
     *************************************************************************/
    void dump_tree() { dump_tree(std::cout); }
    void dump_tree(std::ostream& out) { dump_tree(out, &root); }

    void dump_tree(std::ostream& out, group* p, bool in_progress = false)
    {
        if (!in_progress)
        {
            out << "digraph heap {\n"
                << "  edge[dir=\"back\"];\n";
        }

        size_type p_index = 0;
        if (p != &root)
            while (&index_to_group[p_index] != p)
                ++p_index;

        for (size_type i = 0; i < p->rank; ++i)
        {
            group* c = p->children[i];
            if (c)
            {
                size_type c_index = 0;
                if (c != &root)
                    while (&index_to_group[c_index] != c)
                        ++c_index;

                out << "  ";
                if (p == &root)
                    out << 'p';
                else
                    out << p_index;
                out << " -> ";
                if (c == &root)
                    out << 'p';
                else
                    out << c_index;
                if (A[c->rank] == c)
                    out << " [style=\"dotted\"]";
                out << ";\n";
                dump_tree(out, c, true);

                // Emit node information
                out << "  ";
                if (c == &root)
                    out << 'p';
                else
                    out << c_index;
                out << " [label=\"";
                if (c == &root)
                    out << 'p';
                else
                    out << c_index;
                out << ":";
                size_type start = c_index * log_n;
                size_type end = start + log_n;
                if (end > groups.size())
                    end = groups.size();
                while (start != end)
                {
                    if (groups[start])
                    {
                        out << " " << get(id, *groups[start]);
                        if (*groups[start] == *c->value)
                            out << "(*)";
                    }
                    ++start;
                }
                out << '"';

                if (do_compare(c, p))
                {
                    out << "  ";
                    if (c == &root)
                        out << 'p';
                    else
                        out << c_index;
                    out << ", style=\"filled\", fillcolor=\"gray\"";
                }
                out << "];\n";
            }
            else
            {
                assert(p->parent == p);
            }
        }
        if (!in_progress)
            out << "}\n";
    }

    bool valid()
    {
        // Check that the ranks in the A array match the ranks of the
        // groups stored there. Also, the active groups must be the last
        // child of their parent.
        for (size_type r = 0; r < A.size(); ++r)
        {
            if (A[r] && A[r]->rank != r)
                return false;

            if (A[r] && A[r]->parent->children[A[r]->parent->rank - 1] != A[r])
                return false;
        }

        // The root must have no value and a key of -Infinity
        if (root.kind != smallest_key)
            return false;

        return valid(&root);
    }

    bool valid(group* p)
    {
        for (size_type i = 0; i < p->rank; ++i)
        {
            group* c = p->children[i];
            if (c)
            {
                // Check link structure
                if (c->parent != p)
                    return false;
                if (c->rank != i)
                    return false;

                // A bad group must be active
                if (do_compare(c, p) && A[i] != c)
                    return false;

                // Check recursively
                if (!valid(c))
                    return false;
            }
            else
            {
                // Only the root may
                if (p != &root)
                    return false;
            }
        }
        return true;
    }

#endif // BOOST_RELAXED_HEAP_DEBUG

private:
    size_type build_tree(
        group& parent, size_type idx, size_type r, size_type max_rank)
    {
        group& this_group = index_to_group[idx];
        this_group.parent = &parent;
        ++idx;

        this_group.children = root.children + (idx * max_rank);
        this_group.rank = r;
        for (size_type i = 0; i < r; ++i)
        {
            this_group.children[i] = &index_to_group[idx];
            idx = build_tree(this_group, idx, i, max_rank);
        }
        return idx;
    }

    void find_smallest() const
    {
        group** roots = root.children;

        if (!smallest_value)
        {
            std::size_t i;
            for (i = 0; i < root.rank; ++i)
            {
                if (roots[i]
                    && (!smallest_value
                        || do_compare(roots[i], smallest_value)))
                {
                    smallest_value = roots[i];
                }
            }
            for (i = 0; i < A.size(); ++i)
            {
                if (A[i]
                    && (!smallest_value || do_compare(A[i], smallest_value)))
                    smallest_value = A[i];
            }
        }
    }

    bool do_compare(group* x, group* y) const
    {
        return (x->kind < y->kind
            || (x->kind == y->kind && x->kind == stored_key
                && compare(*x->value, *y->value)));
    }

    void promote(group* a)
    {
        assert(a != 0);
        rank_type r = a->rank;
        group* p = a->parent;
        assert(p != 0);
        if (do_compare(a, p))
        {
            // s is the rank + 1 sibling
            group* s = p->rank > r + 1 ? p->children[r + 1] : 0;

            // If a is the last child of p
            if (r == p->rank - 1)
            {
                if (!A[r])
                    A[r] = a;
                else if (A[r] != a)
                    pair_transform(a);
            }
            else
            {
                assert(s != 0);
                if (A[r + 1] == s)
                    active_sibling_transform(a, s);
                else
                    good_sibling_transform(a, s);
            }
        }
    }

    group* combine(group* a1, group* a2)
    {
        assert(a1->rank == a2->rank);
        if (do_compare(a2, a1))
            do_swap(a1, a2);
        a1->children[a1->rank++] = a2;
        a2->parent = a1;
        clean(a1);
        return a1;
    }

    void clean(group* q)
    {
        if (2 > q->rank)
            return;
        group* qp = q->children[q->rank - 1];
        rank_type s = q->rank - 2;
        group* x = q->children[s];
        group* xp = qp->children[s];
        assert(s == x->rank);

        // If x is active, swap x and xp
        if (A[s] == x)
        {
            q->children[s] = xp;
            xp->parent = q;
            qp->children[s] = x;
            x->parent = qp;
        }
    }

    void pair_transform(group* a)
    {
#if defined(BOOST_RELAXED_HEAP_DEBUG) && BOOST_RELAXED_HEAP_DEBUG > 1
        std::cerr << "- pair transform\n";
#endif
        rank_type r = a->rank;

        // p is a's parent
        group* p = a->parent;
        assert(p != 0);

        // g is p's parent (a's grandparent)
        group* g = p->parent;
        assert(g != 0);

        // a' <- A(r)
        assert(A[r] != 0);
        group* ap = A[r];
        assert(ap != 0);

        // A(r) <- nil
        A[r] = 0;

        // let a' have parent p'
        group* pp = ap->parent;
        assert(pp != 0);

        // let a' have grandparent g'
        group* gp = pp->parent;
        assert(gp != 0);

        // Remove a and a' from their parents
        assert(ap
            == pp->children[pp->rank - 1]); // Guaranteed because ap is active
        --pp->rank;

        // Guaranteed by caller
        assert(a == p->children[p->rank - 1]);
        --p->rank;

        // Note: a, ap, p, pp all have rank r
        if (do_compare(pp, p))
        {
            do_swap(a, ap);
            do_swap(p, pp);
            do_swap(g, gp);
        }

        // Assuming k(p) <= k(p')
        // make p' the rank r child of p
        assert(r == p->rank);
        p->children[p->rank++] = pp;
        pp->parent = p;

        // Combine a, ap into a rank r+1 group c
        group* c = combine(a, ap);

        // make c the rank r+1 child of g'
        assert(gp->rank > r + 1);
        gp->children[r + 1] = c;
        c->parent = gp;

#if defined(BOOST_RELAXED_HEAP_DEBUG) && BOOST_RELAXED_HEAP_DEBUG > 1
        std::cerr << "After pair transform...\n";
        dump_tree();
#endif

        if (A[r + 1] == pp)
            A[r + 1] = c;
        else
            promote(c);
    }

    void active_sibling_transform(group* a, group* s)
    {
#if defined(BOOST_RELAXED_HEAP_DEBUG) && BOOST_RELAXED_HEAP_DEBUG > 1
        std::cerr << "- active sibling transform\n";
#endif
        group* p = a->parent;
        group* g = p->parent;

        // remove a, s from their parents
        assert(s->parent == p);
        assert(p->children[p->rank - 1] == s);
        --p->rank;
        assert(p->children[p->rank - 1] == a);
        --p->rank;

        rank_type r = a->rank;
        A[r + 1] = 0;
        a = combine(p, a);
        group* c = combine(a, s);

        // make c the rank r+2 child of g
        assert(g->children[r + 2] == p);
        g->children[r + 2] = c;
        c->parent = g;
        if (A[r + 2] == p)
            A[r + 2] = c;
        else
            promote(c);
    }

    void good_sibling_transform(group* a, group* s)
    {
#if defined(BOOST_RELAXED_HEAP_DEBUG) && BOOST_RELAXED_HEAP_DEBUG > 1
        std::cerr << "- good sibling transform\n";
#endif
        rank_type r = a->rank;
        group* c = s->children[s->rank - 1];
        assert(c->rank == r);
        if (A[r] == c)
        {
#if defined(BOOST_RELAXED_HEAP_DEBUG) && BOOST_RELAXED_HEAP_DEBUG > 1
            std::cerr << "- good sibling pair transform\n";
#endif
            A[r] = 0;
            group* p = a->parent;

            // Remove c from its parent
            --s->rank;

            // Make s the rank r child of p
            s->parent = p;
            p->children[r] = s;

            // combine a, c and let the result by the rank r+1 child of p
            assert(p->rank > r + 1);
            group* x = combine(a, c);
            x->parent = p;
            p->children[r + 1] = x;

            if (A[r + 1] == s)
                A[r + 1] = x;
            else
                promote(x);

#if defined(BOOST_RELAXED_HEAP_DEBUG) && BOOST_RELAXED_HEAP_DEBUG > 1
            dump_tree(std::cerr);
#endif
            //      pair_transform(a);
        }
        else
        {
            // Clean operation
            group* p = a->parent;
            s->children[r] = a;
            a->parent = s;
            p->children[r] = c;
            c->parent = p;

            promote(a);
        }
    }

    static void do_swap(group*& x, group*& y)
    {
        group* tmp = x;
        x = y;
        y = tmp;
    }

    /// Function object that compares two values in the heap
    Compare compare;

    /// Mapping from values to indices in the range [0, n).
    ID id;

    /** The root group of the queue. This group is special because it will
     *  never store a value, but it acts as a parent to all of the
     *  roots. Thus, its list of children is the list of roots.
     */
    group root;

    /** Mapping from the group index of a value to the group associated
     *  with that value. If a value is not in the queue, then the "value"
     *  field will be empty.
     */
    std::vector< group > index_to_group;

    /** Flat data structure containing the values in each of the
     *  groups. It will be indexed via the id of the values. The groups
     *  are each log_n long, with the last group potentially being
     *  smaller.
     */
    std::vector< ::boost::optional< value_type > > groups;

    /** The list of active groups, indexed by rank. When A[r] is null,
     *  there is no active group of rank r. Otherwise, A[r] is the active
     *  group of rank r.
     */
    std::vector< group* > A;

    /** The group containing the smallest value in the queue, which must
     *  be either a root or an active group. If this group is null, then we
     *  will need to search for this group when it is needed.
     */
    mutable group* smallest_value;

    /// Cached value log_base_2(n)
    size_type log_n;
};

} // end namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_RELAXED_HEAP_HEADER

/* relaxed_heap.hpp
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
*/