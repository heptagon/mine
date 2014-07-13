abstract class sorter {

	def sort ( x: List[Int] ) : List[Int] 
	def verify(x:List[Int], comp : (Int,Int)=>Boolean ) : Boolean  = x match  {
		case Nil => true	
		case x :: xs => xs == Nil || ( comp(x,xs.head) && verify(xs,comp)) 
	}
}

object test extends sorter {
	def sort ( x:List[Int] ): List[Int] = List()

	def < ( a: Int, b: Int) : Boolean = a < b
	def > ( a: Int, b: Int) : Boolean = a > b

	def main ( args : Array[String] ) :Unit = {
		var x = List ( 1, 2 ,3 ,4)
		if ( verify(x,>) ) println (true) else println(false)
}
}

