module Main where

main :: IO ()
main = do
    print (fact 19)

fact n = product [1..n]
