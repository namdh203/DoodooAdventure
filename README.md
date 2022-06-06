# Doodoo Adventure
Họ tên : Dương Hồng Nam  
MSSV : 21020024  
Lớp : K66C-CLC  
## Giới thiệu
Người chơi điều khiển nhân vật chiến đấu với quái vật  
Link game demo : https://www.youtube.com/watch?v=xJo4eg7-pzI  

## Thư viện sử dụng  
SDL2-2.0.20, SDL2_image-2.0.5, SDL2_mixer-2.0.4  

## Hướng dẫn chơi  
* Nhấn phím A, D để di chuyển sang trái, phải  
* Nhấn phím J để tấn công  
* Nhấn phím K để nhảy  
* Nhấn phím L để trượt  
* Nhấn phím Esc để tạm dừng trò chơi   

## Thiết kế map 
Game gồm có 6 map, tất cả các map được tạo bởi **Tiled**   
Link tải Tiled : https://www.mapeditor.org/download.html  
Về phần nhân vật, quái vật, boss, cũng như là tileset được lấy từ https://itch.io/

## Thuật toán 
* Map có kích thước 736 x 480 và được chia thành các ô vuông có kích thước 32 x 32.  
* Vì vậy em sử dụng một mảng 2 chiều để lưu trạng thái của các ô (0 là đi qua được, 1 là bị chặn, 2 là bị chặn nhưng dùng để tạo ra quái vật)  
* Mỗi hàng của mảng 2 chiều mang giá trị 2 chỉ được tạo ra tối đa 2 quái.  
* Trong trường hợp chỉ có một hàng thì được tạo nhiều hơn 2 quái.  
* Muốn qua được màn chơi tiếp theo thì cần phải hạ gục được hết quái vật trong màn chơi hiện tại.  
* Sau khi hoàn thành tất cả màn chơi, nhấn phím J để trở về menu của game.  
