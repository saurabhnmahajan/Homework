import cv2
 
img = cv2.imread('img.jpg')

new_img = cv2.resize(img, (0,0), fx=1.75, fy=1.75) 

cv2.namedWindow('Original image')
cv2.imshow('Original image', img)

cv2.namedWindow('Magnified image')
cv2.imshow('Magnified image', new_img)

cv2.waitKey(0)
cv2.destroyAllWindows()