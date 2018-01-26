# rooted-tree-html-generator
A C++ school project that generates a rooted-tree of mathematical expressions and its graph in HTML.

You can find an example page [here](http://mrkelisi.com/f/rooted-tree-demo.html).

## 1. Display the tree of a mathematical expression in console

The common goal of this project was to code an abstract data type of mathematical expression in a rooted-tree structure and be able to:
- copy a tree
- tell if a tree is constant
- tell if two trees are equals
- derivate a tree
- simplify a tree
- display a tree in console with tabs

To do so, our rooted-tree ADT has the following structure: 

```
typedef struct Node {
   char Value;
   struct Noeud *left, *right;
} TNode, *TExprArb;
```

**The primitives are:**

- `TExprArb ConsF(char X)` creates a leaf with X value.

- `TExprArb Cons2(char X, TExprArb fg, TExprArb fd)` creates a tree from the trees fg and fd, with X value.

- `bool EstFeuille(TExprArb E)` checks if the tree E is a leaf.

- `char Racine(TExprArb A)` returns the root of the tree A.

- `TExprArb Fg(TExprArb A)` returns the left branch of the tree A.

- `TExprArb Fd(TExprArb A)` returns the right branch of the tree A.

To display the tree in console with a 90° angle to the left, we create the procedure `void AfficherEAAArb(TExprArb E, int n)` that use a switch on the root of the tree E, and recursively call the display function `AfficherEAAArb` on both branches with the correct order :
1. Display function on the right branch, with n+3 spaces in front
2. Root value, with n spaces in front
3. Display function on the left branch, with n+3 spaces in front

![img-rooted-tree-console](http://mrkelisi.com/f/rooted-tree-1.png)

## 2. Display the tree of a mathematical expression in HTML
Beside the main project, we were asked to code a unique function that exploit rooted-tree ADT. This one was @Madeorsk 's personnal project.

To create the tree, a function calculates the width needed to the left and the one needed to the right, display the root in a circle at the right place, and draw two branches with the correct angle and width based on the children's width.
Then it calls the function on each child again until the leaves.

Branches beneath a node can shrink if you click on the node, and branches will become dotted.

![img-rooted-tree-html](http://mrkelisi.com/f/rooted-tree-2.png)

## 3. Display the graph of a mathematical expression in HTML
This function was @MrKelisi 's personnal project.

The graph can be set with a custom window size, and a function will create, with a defined number of segments, each curve in a svg polyline.

To display the curves' values, I use javascript to track the mouse position, transform it into a x number for the graph, and use the polylines to calculate the y number of each curve. Dots follow the mouse along the curves for better view.

![img-function-curve-html](http://mrkelisi.com/f/rooted-tree-3.png)
