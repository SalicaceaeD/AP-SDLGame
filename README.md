# Mini-Golf
Trần Thùy Dương
21020010 - K66C-CLC

## Introduction
Bài tập lớn - Game (môn học: Lập trình Nâng cao - INT2215 2)

### Table of Contents
**[Started](#started)**  
**[References](#references)**  
**[Overview](#overview)**  
**[Demo Videos](#demo-videos)**  

## Started

### Ideas
Ý tưởng cho bài tập lớn là game mini golf với góc nhìn top-down, thêm một số yếu tố đặc biệt.

### Prepared
Để chuẩn bị cho bài tập lớn, em cần chuẩn bị những kiến thức sau:
- Kiến thức nền tảng: C++
- Kiến thức về OOP của C++ (chủ yếu là class)
- Kiến thức để sử dụng thư viện SDL2 
- Kiến thức về lập trình ứng dụng, cụ thể là game:
  * Cách tổ chức chương trình
  * Cách chia file
  * Cách quản lý các thành phần của game
- Tài nguyên của game:
  * Hình ảnh (png): tự vẽ trên nền tảng [pixilart](https://www.pixilart.com)
  * Âm thanh (mp3): lấy từ một số nguồn miễn phí
  * Font chữ (ttf): tự làm trên nền tảng [fontstruct](https://fontstruct.com)
- Thời gian để thu thập những thứ trên

## References
Để chuẩn bị cho bài tập lớn em đã:
- Đoc tài liệu, slide và làm bài tập
- Học cách cài đặt và sử dụng SDL2 cùng các thư viện đi kèm (image, mixer, ttf) trên [lazyfoo](https://lazyfoo.net/tutorials/SDL/)
- Tham khảo khung chương trình và cách tổ chức game từ video và repository của Youtuber [PolyMars](https://www.youtube.com/watch?v=iEn0ozP-jxc)
- Tham khảo đồ họa và các tính năng từ game [Nano Golf](https://www.youtube.com/watch?v=EeX57BjFxHI)

## Overview

### Playing
Game gồm 25 level:
Mỗi level bao gồm:
- Golf ball: do người chơi tác động để di chuyển trên sân golf
- Golf hole: đích đến của golf ball
- Stroke: lần đánh bóng
- Time: thời gian chơi
- Một số yếu tố đặc biệt xuất hiện trong những level cụ thể:
    * Block: golf ball sẽ bật lại khi đập vào block
    * Water: nếu golf ball rơi xuống water, game kết thúc
    * Pyramid: sau khi golf ball đi vào pyramid, hướng đi tiếp theo của golf ball được random theo 4 hướng
    * Lock & Key: lock sẽ khóa golf hole lại, số khóa được ghi trên lock; golf ball phải thu thập đủ các chìa bằng cách đi qua các vùng key trước khi có thể tiếp cận golf hole
    * Teleport gate: một teleport gate gồm 2 cổng, golf ball sau khi đi vào một cổng sẽ được đưa đến cổng còn lại, hướng đi và vận tốc của golf ball được giữ nguyên
Nhiệm vụ của người chơi là đưa golf ball đến golf hole với số stroke và time ít nhất có thể

### Control
Người chơi hoàn toàn sử dụng chuột để chơi game:
- Nhấp chuột để chọn level, menu, options,...
- Kéo thả chuột để cung cấp hướng và vận tốc ban đầu cho golf ball

## Demo videos
[Link drive các video demo về game](https://drive.google.com/drive/folders/1xE2aG9UJGwi5CJDW72hMgvDbyT6QGc2B?usp=sharing)
Bao gồm 2 video:
- 1 video về Menu và Setting của game
- 1 video về demo gameplay của game
