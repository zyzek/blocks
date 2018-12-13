module Fractal where

import Data.Complex

thresh = 5.0 :: Double
maxIter = 20 :: Integer
power = 2 :: Integer

scale = 0.6 :: Double
width = 400 :: Integer
height = 600 :: Integer
step = 2.0 / (scale * fromIntegral width) :: Double

yRescale = 0.5 :: Double
xOffset = 1.5 * (fromIntegral width * step / 2.0)
yOffset = (fromIntegral height * step / 2.0)

iterator :: (Integer -> Complex Double -> Complex Double -> Complex Double) -> Double -> Integer -> Complex Double -> Integer -> Complex Double -> Integer
iterator f threshold maxIterations c iterations z
    | iterations >= maxIterations = iterations
    | realPart (abs z) >= threshold = iterations
    | otherwise = iterator f threshold maxIterations c (iterations + 1) (f iterations z c)

mandel :: Integer -> Integer -> Complex Double -> Complex Double -> Complex Double
mandel d iterations z c = z^d + c

iterFunc :: Integer -> Integer -> Complex Double -> Complex Double -> Complex Double
iterFunc d iterations z c = z^d + c * (0 :+ (pi * (fromIntegral iterations) / 12))

fractal :: Complex Double -> Integer
fractal c = iterator (mandel power) thresh maxIter c 0 (0 :+ 0)

transformWidth :: Integer -> Double
transformWidth p = (fromIntegral p) * step - xOffset
transformHeight p = yRescale * ((fromIntegral p) * step - yOffset)

iters :: [[Integer]]
iters = [[ fractal (x :+ y)
         | y <- map transformHeight [0..height]]
        | x <- map transformWidth [0..width]] 

iterToChar :: Integer -> Char
iterToChar i
 | i < 5 = ' '
 | i < 10 = '.'
 | i < 15 = 'o'
 | i < 20 = 'O'
 | otherwise = '0'

res :: String
res = (concatMap (\row -> (map iterToChar row) ++ "\n") iters)

-- (zoom out the terminal)
main = do
    putStrLn res
