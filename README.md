# ThiefGame
- [Thử nghiệm game](https://drive.google.com/file/d/1ZT0dikVM6xklZ4AU085tSgMDWoH_w_2J/view?usp=sharing)
# Giới thiệu Game:
ThiefGame là 1 game thuộc dạng "hoán đổi vai trò". Thay vì bạn sẽ đóng vai là kẻ trộm và đi trộm đồ như thông thường thì bây giờ bạn sẽ là một tên trộm hoàn lương, đem những món mà mình đã trộm đi trả lại vào đúng vị trí cho chủ nhà, sao cho chủ nhà (và con chó) không phát hiện ra bạn. Nếu không, trò chơi sẽ kết thúc và bạn bị bắt. Lúc đó sẽ không còn cơ hội để bạn hoàn lương.   
  
Ý tưởng gốc của Game: https://www.youtube.com/watch?v=kBTDEqO6jj4&list=WL&index=8  
  
- [CÁCH TẢI GAME](#cách-tải-game)
- [Bắt đầu game](#bắt-đầu-game)
- [Các thành phần trong game](#các-thành-phần-trong-game)
- [Cách chơi](#cách-chơi)
- [Chiến thắng/Thất bại](#chiến-thắng-và-thất-bại)
- [Đồ họa](#đồ-họa)
- [Source Code](#source-code)


## CÁCH TẢI GAME
1. KHÔNG BAO GỒM CODE: Cách này giúp tiết kiệm bộ nhớ và thời gian tải vì sau khi giải nén chỉ chiếm khoảng 10MB.  
- Game được nén thành file zip tại link sau: (https://github.com/hnahk05/ThiefGame/releases/tag/game_nocode)
- Cách thực hiện: Tải về, giải nén và chọn ProjectTest.exe để chơi.  
2. BAO GỒM CODE - CÓ THỂ BIÊN DỊCH:
- Bước 1: Chọn Code -> Download Zip (6,6MB)
![Ảnh minh họa](https://i.imgur.com/VTwS6rc.png)
![Ảnh minh họa](https://i.imgur.com/mRiuSH9.png)
- Bước 2: Bật ProjectTest.exe và chơi
## BẮT ĐẦU GAME
![màn_hình_bắt_đầu](https://i.imgur.com/1ZkP8TF.png)  
Để bắt đầu chơi, click chuột vào "START", giảm âm lượng nếu nhạc nền quá lớn. 
## CÁC THÀNH PHẦN TRONG GAME
- Nhân vật trong game: Tên trộm mà bạn phải hóa thân thành.  
![tên trộm](https://i.imgur.com/lf3OELP.png)  
- Background (căn nhà mà trộm "hành nghề" tại đó): 
![sơ đồ căn nhà](https://i.imgur.com/p6Y66Qw.png)  
- Các items: những đồ vật mà nhân vật phải đem đi trả lại:  
![chai rượu](https://i.imgur.com/GLNEkB2.png) chai rượu  
![điện thoại](https://i.imgur.com/4dnmYOb.png) điện thoại  
![máy tính bàn](https://i.imgur.com/2TEWbvI.png) máy tính bàn  
![đồng hồ đeo tay](https://i.imgur.com/aNO2z68.png) đồng hồ đeo tay  
![túi tiền](https://i.imgur.com/0D4S9Wo.png) túi tiền  
- Thanh noise: thanh tiếng động, khi bạn chạm vào đồ vật không liên quan thì thanh này sẽ đầy.  
![noise](https://i.imgur.com/k4kNPP0.png) thanh noise ban đầu  
![noise](https://i.imgur.com/REZ568B.png) thanh noise khi bạn đã va chạm
## CÁCH CHƠI
Lấy đồ từ xe tải và đem nó về các điểm trả đồ trong căn nhà. Lưu ý rằng đồ từ trong xe tải sẽ random. Bạn sẽ có 1 thanh noise. Đừng chạm vào quá nhiều đồ đạc không liên quan nếu không muốn thanh noise đó đầy, khi nó đầy thì mọi người sẽ thức dậy và bạn bị bắt. Lúc đó bạn sẽ bị bắt.   
- Đầu tiên, hãy tiến đến gần xe tải, bấm "E" để lấy đồ.  
- Sau đó, đem những đồ vật tương ứng với hình ảnh đem trả tại các điểm trả đồ. Nếu bạn trả không đúng thì thanh noise sẽ tăng, nếu đúng thì điểm trả đồ đó sẽ biến mất, bạn cũng không còn cầm item đó nữa.  
- Sau khi kết thúc game, bấm "E" để chơi lại.
## CHIẾN THẮNG VÀ THẤT BẠI
- Bạn sẽ chiến thắng nếu trả hết đồ đạc trong nhà mà không bị chủ nhà phát hiện.  
![chiến thắng](https://i.imgur.com/Ih382Vi.jpeg)  
- Bạn sẽ thất bại khi thanh noise đầy, bạn đã bị phát hiện.  
![thất bại](https://i.imgur.com/xgjiF3b.jpeg)
## ĐỒ HỌA
Background căn nhà: [Eden Eldersong Facebook](https://www.facebook.com/photo.php?fbid=287421350458352&set=pb.100075714660560.-2207520000&type=3)  
## SOURCE CODE
- Folder assets: Chứa các ảnh sử dụng trong game như items, nhân vật, background,...  
- Folder audio: Chứa âm thanh được sử dụng trong game.
- Folder src: Chứa code của game  
    - GameFull:
        - Khởi tạo âm thanh cho game.
        - Khởi tạo màn hình bắt đầu, nút start, và màn hình kết thúc game.
        - Xử lí đầu vào từ bàn phím (cụ thể là phím "E" để chơi game, reset game)
        - Xử lí va chạm
    - Graphics:
        - Xử lí đồ họa, vẽ màn hình game.
        - Vẽ thanh tiếng ồn.
    - House: Xử lí va chạm với ngôi nhà của nhân vật.
    - Item: Xử lí việc nhặt vật phẩm, hiện vật phẩm và trả đồ.
    - Thief: Xử lí các phần liên quan đến nhân vật trộm.
        - Load các texture điểm trả đồ của items và xử lí việc trả đồ liên quan đến texture đó.
        - Điều khiển nhân vật.
        - Xử lí việc trả đồ của nhân vật.
        - Vẽ camera theo nhân vật.
    - defs.h: Các hằng số sử dụng trong game.
- main.cpp: Hàm main() của game.

