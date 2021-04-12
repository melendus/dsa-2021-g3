# Lab 07

> In this lab we talked about graphs, learned how to implement them in 3 different ways
> Also learned how 2 traversals work, BFS and DFS
> learned how to implement Dijkstra’s algorithm
>P.S i will send the extra assigment after the deadline with like 20 minutes, I hope it still counts :(


> How I solved the extra:

1) First I read the number of lines and created a matrix of dimension nr*2 because we only read 2 numbers on each line
2) Based on this array, I created an adjacency matrix
3) I created a linked list in which I put in order all the nodes, like this 1->2->3->4->...->n   n being the biggest node
4) After that, when I encountered in the adjacency matrix a 1 at a position in which i was bigger than j, I switched the nodes in the linked list
5) I made a special function which changes two nodes in a list


