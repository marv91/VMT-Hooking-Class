# VMT Hooking Class

usage:

t y p e d e f   v o i d ( _ _ t h i s c a l l   * f u n c A _ t ) ( v o i d * ) ; 
 
 f u n c A _ t   o F u n c A ; 
 
 
 
 v o i d   h k F u n c A ( )   { 
 
 	 c o u t   < <   " h i j a c k e d   f u n c A   w a s   c a l l e d \ n " ; 
 
 	 o F u n c A ( g _ p C l a s s ) ; 
 
 } 
 


 
 	 u n i q u e _ p t r < V M T H o o k >   C l a s s V M T ( V M T H o o k : : C r e a t e < M y C l a s s > ( g _ p C l a s s ) ) ; 
 
 	 o F u n c A   =   C l a s s V M T - > H o o k F u n c t i o n < f u n c A _ t > ( 0 ,   & h k F u n c A ) ; 
 
