# Minesweep
<Minesweeper>

Luật chơi cơ bản:
Người chơi sẽ được đưa ra 1 ma trận gồm 10 hàng và 10 cột, trong ma trận sẽ có những quả mìn (kí hiệu “X”) được setup ngẫu nhiên. Người chơi sẽ nhập “o” nếu muốn mở 1 ô và nhập “f” nếu muốn đặt cờ (kí hiệu “F”) lên 1 ô bằng cách nhập vị trí ô đó. Trò chơi sẽ kết thúc nếu người chơi mở ô có mìn, số hiện trên mỗi ô biểu thị số mìn xung quanh ô đó.
\nCác tính năng hiện tại game có:
- 3 chế độ chơi ở ma trận 10*10:
  + Dễ (Easy): 10 quả mìn được setup ngẫu nhiên
  + Trung bình (Medium): 15 quả mìn được setup ngẫu nhiên
  + Khó (Easy): 20 quả mìn được setup ngẫu nhiên
- Có hiển thị tổng thời gian ở các nước đi
- Có hiển thị số cờ đã đặt trên ma trận
\nPhát triển trong tương lai:
- Mở rộng phạm vi ma trận (có thể lên 20*20 hoặc lớn hơn)
- Sử dụng SDL2 tạo âm thanh, hoạt ảnh cho trò chơi thay vì text ở thời điểm hiện tại
