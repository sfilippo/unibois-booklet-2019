/*
  Rotating calipers:
  	A pair of parallel lines that can be rotated
  	around the polygon and “holds” it as tight as possible

  I hope you won't need this.
  But as you are here, let's see what we have:
  	(assuming we want farthest points)
  1) build convex hull
  2) pick any normal vector ? and find calipers
  	that match this vector:
  		(I assume this means that you pick any two hull-edges)
	3) Test the points facing the calipers
  4) find minimum angle to get next point
  5) rotate calipers by that angle
  6) if state is already visited, stop the calipers

	The above runs in O(N), assuming you can code it.
*/
