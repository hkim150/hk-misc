import Cocoa

let a: Int -> Int
a = {$0 + 2}
print(a(3))

let b: (Int, Int) -> Int
b = {$0 + $1}
print(b(2,3))

let array = [1,2,3]
let c: Int -> Int
c = {$0 * 2}
print(array.map(c))

let array2 = [2,3,4]
print(array2.map({$0 + 1}))

var array3 = [1,2,3,4]
array3 = array3.map({$0 * 5})
print(array3)