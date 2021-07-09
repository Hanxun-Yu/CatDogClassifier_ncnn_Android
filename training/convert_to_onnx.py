"""
This code is used to convert the pytorch models into an onnx format models.
"""
import torch.onnx
from net.VGG_192x192 import VGG_192x192

input_img_size = 112  # define input size

model_path = "./VGG_192x192_models/20.pth"
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

checkpoint = torch.load(model_path, map_location=device)
net = PFLDInference()
net.load_state_dict(checkpoint)
net.eval()
net.to(device)

model_name = model_path.split("/")[-1].split(".")[0]
model_path = f"models/checkpoint/0_25/list25p_gray_rgb_shake3w_shake17w_shake7w/{model_name}.onnx"

dummy_input = torch.randn(1, 3, 112, 112).to(device)

torch.onnx.export(net, dummy_input, model_path, export_params=True, verbose=False, input_names=['input'], output_names=['pose', 'landms'])
