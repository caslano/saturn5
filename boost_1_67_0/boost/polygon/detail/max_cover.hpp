/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_MAX_COVER_HPP
#define BOOST_POLYGON_MAX_COVER_HPP
namespace boost { namespace polygon{

  template <typename Unit>
  struct MaxCover {
    typedef interval_data<Unit> Interval;
    typedef rectangle_data<Unit> Rectangle;

    class Node {
    private:
      std::vector<Node*> children_;
      std::set<Interval> tracedPaths_;
    public:
      Rectangle rect;
      Node() : children_(), tracedPaths_(), rect() {}
      Node(const Rectangle rectIn) : children_(), tracedPaths_(), rect(rectIn) {}
      typedef typename std::vector<Node*>::iterator iterator;
      inline iterator begin() { return children_.begin(); }
      inline iterator end() { return children_.end(); }
      inline void add(Node* child) { children_.push_back(child); }
      inline bool tracedPath(const Interval& ivl) const {
        return tracedPaths_.find(ivl) != tracedPaths_.end();
      }
      inline void addPath(const Interval& ivl) {
        tracedPaths_.insert(tracedPaths_.end(), ivl);
      }
    };

    typedef std::pair<std::pair<Unit, Interval>, Node* > EdgeAssociation;

    class lessEdgeAssociation {
    public:
      typedef const EdgeAssociation& first_argument_type;
      typedef const EdgeAssociation& second_argument_type;
      typedef bool result_type;
      inline lessEdgeAssociation() {}
      inline bool operator () (const EdgeAssociation& elem1, const EdgeAssociation& elem2) const {
        if(elem1.first.first < elem2.first.first) return true;
        if(elem1.first.first > elem2.first.first) return false;
        return elem1.first.second < elem2.first.second;
      }
    };

    template <class cT>
    static inline void getMaxCover(cT& outputContainer, Node* node, orientation_2d orient) {
      Interval rectIvl = node->rect.get(orient);
      if(node->tracedPath(rectIvl)) {
        return;
      }
      node->addPath(rectIvl);
      if(node->begin() == node->end()) {
        //std::cout << "WRITE OUT 3: " << node->rect << std::endl;
        outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(node->rect));
        return;
      }
      bool writeOut = true;
      for(typename Node::iterator itr = node->begin(); itr != node->end(); ++itr) {
        getMaxCover(outputContainer, *itr, orient, node->rect); //get rectangles down path
        Interval nodeIvl = (*itr)->rect.get(orient);
        if(contains(nodeIvl, rectIvl, true)) writeOut = false;
      }
      if(writeOut) {
        //std::cout << "WRITE OUT 2: " << node->rect << std::endl;
        outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(node->rect));
      }
    }

    struct stack_element {
      inline stack_element() :
        node(), rect(), itr() {}
      inline stack_element(Node* n,
                           const Rectangle& r,
                           typename Node::iterator i) :
        node(n), rect(r), itr(i) {}
      Node* node;
      Rectangle rect;
      typename Node::iterator itr;
    };

    template <class cT>
    static inline void getMaxCover(cT& outputContainer, Node* node, orientation_2d orient,
                                   Rectangle rect) {
      //std::cout << "New Root\n";
      std::vector<stack_element> stack;
      typename Node::iterator itr = node->begin();
      do {
        //std::cout << "LOOP\n";
        //std::cout << node->rect << std::endl;
        Interval rectIvl = rect.get(orient);
        Interval nodeIvl = node->rect.get(orient);
        bool iresult = intersect(rectIvl, nodeIvl, false);
        bool tresult = !node->tracedPath(rectIvl);
        //std::cout << (itr != node->end()) << " " << iresult << " " << tresult << std::endl;
        Rectangle nextRect1 = Rectangle(rectIvl, rectIvl);
        Unit low = rect.get(orient.get_perpendicular()).low();
        Unit high = node->rect.get(orient.get_perpendicular()).high();
        nextRect1.set(orient.get_perpendicular(), Interval(low, high));
        if(iresult && tresult) {
          node->addPath(rectIvl);
          bool writeOut = true;
          //check further visibility beyond this node
          for(typename Node::iterator itr2 = node->begin(); itr2 != node->end(); ++itr2) {
            Interval nodeIvl3 = (*itr2)->rect.get(orient);
            //if a child of this node can contain the interval then we can extend through
            if(contains(nodeIvl3, rectIvl, true)) writeOut = false;
            //std::cout << "child " << (*itr2)->rect << std::endl;
          }
          Rectangle nextRect2 = Rectangle(rectIvl, rectIvl);
          Unit low2 = rect.get(orient.get_perpendicular()).low();
          Unit high2 = node->rect.get(orient.get_perpendicular()).high();
          nextRect2.set(orient.get_perpendicular(), Interval(low2, high2));
          if(writeOut) {
            //std::cout << "write out " << nextRect << std::endl;
            outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(nextRect2));
          } else {
            //std::cout << "suppress " << nextRect << std::endl;
          }
        }
        if(itr != node->end() && iresult && tresult) {
          //std::cout << "recurse into child\n";
          stack.push_back(stack_element(node, rect, itr));
          rect = nextRect1;
          node = *itr;
          itr = node->begin();
        } else {
          if(!stack.empty()) {
            //std::cout << "recurse out of child\n";
            node = stack.back().node;
            rect = stack.back().rect;
            itr = stack.back().itr;
            stack.pop_back();
          } else {
            //std::cout << "empty stack\n";
            //if there were no children of the root node
//             Rectangle nextRect = Rectangle(rectIvl, rectIvl);
//             Unit low = rect.get(orient.get_perpendicular()).low();
//             Unit high = node->rect.get(orient.get_perpendicular()).high();
//             nextRect.set(orient.get_perpendicular(), Interval(low, high));
//             outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(nextRect));
          }
          //std::cout << "increment " << (itr != node->end()) << std::endl;
          if(itr != node->end()) {
            ++itr;
            if(itr != node->end()) {
              //std::cout << "recurse into next child.\n";
              stack.push_back(stack_element(node, rect, itr));
              Interval rectIvl2 = rect.get(orient);
              Interval nodeIvl2 = node->rect.get(orient);
              /*bool iresult =*/ intersect(rectIvl2, nodeIvl2, false);
              Rectangle nextRect2 = Rectangle(rectIvl2, rectIvl2);
              Unit low2 = rect.get(orient.get_perpendicular()).low();
              Unit high2 = node->rect.get(orient.get_perpendicular()).high();
              nextRect2.set(orient.get_perpendicular(), Interval(low2, high2));
              rect = nextRect2;
              //std::cout << "rect for next child" << rect << std::endl;
              node = *itr;
              itr = node->begin();
            }
          }
        }
      } while(!stack.empty() || itr != node->end());
    }

    /*  Function recursive version of getMaxCover
        Because the code is so much simpler than the loop algorithm I retain it for clarity

    template <class cT>
    static inline void getMaxCover(cT& outputContainer, Node* node, orientation_2d orient,
                                   const Rectangle& rect) {
      Interval rectIvl = rect.get(orient);
      Interval nodeIvl = node->rect.get(orient);
      if(!intersect(rectIvl, nodeIvl, false)) {
        return;
      }
      if(node->tracedPath(rectIvl)) {
        return;
      }
      node->addPath(rectIvl);
      Rectangle nextRect(rectIvl, rectIvl);
      Unit low = rect.get(orient.get_perpendicular()).low();
      Unit high = node->rect.get(orient.get_perpendicular()).high();
      nextRect.set(orient.get_perpendicular(), Interval(low, high));
      bool writeOut = true;
      rectIvl = nextRect.get(orient);
      for(typename Node::iterator itr = node->begin(); itr != node->end(); ++itr) {
        nodeIvl = (*itr)->rect.get(orient);
        if(contains(nodeIvl, rectIvl, true)) writeOut = false;
      }
      if(writeOut) {
        outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(nextRect));
      }
      for(typename Node::iterator itr = node->begin(); itr != node->end(); ++itr) {
        getMaxCover(outputContainer, *itr, orient, nextRect);
      }
    }
    */

    //iterator range is assummed to be in topological order meaning all node's trailing
    //edges are in sorted order
    template <class iT>
    static inline void computeDag(iT beginNode, iT endNode, orientation_2d orient,
                                  std::size_t size) {
      std::vector<EdgeAssociation> leadingEdges;
      leadingEdges.reserve(size);
      for(iT iter = beginNode; iter != endNode; ++iter) {
        Node* nodep = &(*iter);
        Unit leading = nodep->rect.get(orient.get_perpendicular()).low();
        Interval rectIvl = nodep->rect.get(orient);
        leadingEdges.push_back(EdgeAssociation(std::pair<Unit, Interval>(leading, rectIvl), nodep));
      }
      polygon_sort(leadingEdges.begin(), leadingEdges.end(), lessEdgeAssociation());
      typename std::vector<EdgeAssociation>::iterator leadingBegin = leadingEdges.begin();
      iT trailingBegin = beginNode;
      while(leadingBegin != leadingEdges.end()) {
        EdgeAssociation& leadingSegment = (*leadingBegin);
        Unit trailing = (*trailingBegin).rect.get(orient.get_perpendicular()).high();
        Interval ivl = (*trailingBegin).rect.get(orient);
        std::pair<Unit, Interval> trailingSegment(trailing, ivl);
        if(leadingSegment.first.first < trailingSegment.first) {
          ++leadingBegin;
          continue;
        }
        if(leadingSegment.first.first > trailingSegment.first) {
          ++trailingBegin;
          continue;
        }
        if(leadingSegment.first.second.high() <= trailingSegment.second.low()) {
          ++leadingBegin;
          continue;
        }
        if(trailingSegment.second.high() <= leadingSegment.first.second.low()) {
          ++trailingBegin;
          continue;
        }
        //leading segment intersects trailing segment
        (*trailingBegin).add((*leadingBegin).second);
        if(leadingSegment.first.second.high() > trailingSegment.second.high()) {
          ++trailingBegin;
          continue;
        }
        if(trailingSegment.second.high() > leadingSegment.first.second.high()) {
          ++leadingBegin;
          continue;
        }
        ++leadingBegin;
        ++trailingBegin;
      }
    }

    template <class cT>
    static inline void getMaxCover(cT& outputContainer,
                                   const std::vector<Rectangle>& rects, orientation_2d orient) {
      if(rects.empty()) return;
      std::vector<Node> nodes;
      {
        if(rects.size() == 1) {
          outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(rects[0]));
          return;
        }
        nodes.reserve(rects.size());
        for(std::size_t i = 0; i < rects.size(); ++i) { nodes.push_back(Node(rects[i])); }
      }
      computeDag(nodes.begin(), nodes.end(), orient, nodes.size());
      for(std::size_t i = 0; i < nodes.size(); ++i) {
        getMaxCover(outputContainer, &(nodes[i]), orient);
      }
    }

  };
}
}

#endif

/* max_cover.hpp
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
*/