# rooted-tree-html-generator
A school project in C++ that generates rooted-trees of mathematical expressions and their graph in HTML.

You can find an [example page here](http://htmlpreview.github.io/?https://github.com/MrKelisi/rooted-tree-html-generator/blob/master/Exemple.html).

# 1. Display the tree of a mathematical expression in a console

The common goal of this project for all students was to code an abstract data type of mathematical expression in a rooted-tree structure that would be able to:
- copy a tree
- tell if a tree is a constant
- tell if two trees are equals
- derivate a tree
- simplify a tree
- display a tree in console with tabulations

To do so, our rooted-tree ADT has the following structure: 

```
typedef struct Node {
   char Value;
   struct Noeud *left, *right;
} TNode, *TExprArb;
```

**The primitives are:**

- `TExprArb ConsF(char X)` creates a leaf with a value X.

- `TExprArb Cons2(char X, TExprArb fg, TExprArb fd)` creates a tree from the trees fg and fd, with a value X.

- `bool EstFeuille(TExprArb A)` checks if the tree A is a leaf.

- `char Racine(TExprArb A)` returns the root of the tree A.

- `TExprArb Fg(TExprArb A)` returns the left branch of the tree A.

- `TExprArb Fd(TExprArb A)` returns the right branch of the tree A.

To display the tree in console with a 90° angle to the left, we create the procedure `void AfficherEAAArb(TExprArb E, int n)` that uses a switch on the root of the tree E, and recursively call the display function `AfficherEAAArb` on both branches with the correct order :
1. Display function on the right branch, with n+3 spaces in front
2. Root value, with n spaces in front
3. Display function on the left branch, with n+3 spaces in front

![img-rooted-tree-console](https://imgur.com/EcPG5Q3.png)



# 2. Personal additions

Beside the main project, we were asked to code a unique function that exploit rooted-tree ADT in a creative way.

## 2.1 Display the tree of a mathematical expression in HTML
*Author : @Madeorsk*

To create the tree, a function calculates the width needed to the left and the one needed to the right, display the root in a circle at the right place, and draw two branches with the correct angle and width based on the children's width.
Then it calls the function on each child again until the leaves.

Branches beneath a node can shrink if you click on the node, and branches will become dotted.

![img-rooted-tree-subtrees](https://imgur.com/4NKqurC.gif)


## 2.2 Display the graph of a mathematical expression in HTML
*Author : @MrKelisi*

The graph can be set with a custom window size, and a function will create, with a defined number of segments, each curve in a svg polyline.

To display the curves' values, I use javascript to track the mouse position, transform it into a x number for the graph, and use the polylines to calculate the y number of each curve. Dots follow the mouse along the curves for better view.

![img-rooted-tree-graph](https://imgur.com/AWXQkrl.gif)