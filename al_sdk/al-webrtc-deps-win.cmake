
SET(WEBRTC_LIBS
  ${WEBRTCBUILD}\\libyuv.lib
  ${WEBRTCBUILD}\\obj\\third_party\\boringssl\\boringssl.lib
  ${WEBRTCBUILD}\\obj\\third_party\\boringssl\\boringssl_asm.lib
  ${WEBRTCBUILD}\\obj\\third_party\\jsoncpp\\jsoncpp.lib
  ${WEBRTCBUILD}\\obj\\third_party\\libjpeg_turbo\\libjpeg.lib
  ${WEBRTCBUILD}\\obj\\third_party\\libsrtp\\libsrtp.lib
  ${WEBRTCBUILD}\\obj\\third_party\\libvpx\\libvpx.lib
  ${WEBRTCBUILD}\\obj\\third_party\\libvpx\\libvpx_intrinsics_avx.lib
  ${WEBRTCBUILD}\\obj\\third_party\\libvpx\\libvpx_intrinsics_avx2.lib
  ${WEBRTCBUILD}\\obj\\third_party\\libvpx\\libvpx_intrinsics_mmx.lib
  ${WEBRTCBUILD}\\obj\\third_party\\libvpx\\libvpx_intrinsics_sse2.lib
  ${WEBRTCBUILD}\\obj\\third_party\\libvpx\\libvpx_intrinsics_sse4_1.lib
  ${WEBRTCBUILD}\\obj\\third_party\\libvpx\\libvpx_intrinsics_ssse3.lib
  ${WEBRTCBUILD}\\obj\\third_party\\openmax_dl\\dl\\openmax_dl.lib
  ${WEBRTCBUILD}\\obj\\third_party\\opus\\opus.lib
  ${WEBRTCBUILD}\\obj\\third_party\\protobuf\\protobuf_full_do_not_use.lib
  ${WEBRTCBUILD}\\obj\\third_party\\protobuf\\protobuf_lite.lib
  ${WEBRTCBUILD}\\obj\\third_party\\protobuf\\protoc_lib.lib
  ${WEBRTCBUILD}\\obj\\third_party\\usrsctp\\usrsctplib.lib
  ${WEBRTCBUILD}\\obj\\third_party\\winsdk_samples\\directshow_baseclasses.lib
  ${WEBRTCBUILD}\\obj\\third_party\\yasm\\genperf_libs.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\rtc_event_log.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\rtc_event_log_parser.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\rtc_event_log_proto.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\webrtc.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\webrtc_common.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\api\\libjingle_peerconnection.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\base\\rtc_base.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\base\\rtc_base_approved.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\base\\rtc_task_queue.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\common_audio\\common_audio.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\common_audio\\common_audio_sse2.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\common_video\\common_video.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\media\\rtc_media.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\audioproc_debug_proto.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\audio_coding_module.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\audio_conference_mixer.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\audio_decoder_factory_interface.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\audio_decoder_interface.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\audio_device.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\audio_encoder_interface.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\audio_mixer.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\audio_processing.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\audio_processing_sse2.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\bitrate_controller.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\builtin_audio_decoder_factory.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\cng.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\congestion_controller.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\desktop_capture.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\desktop_capture_differ_sse2.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\g711.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\g722.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\ilbc.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\isac.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\isac_common.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\isac_fix.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\media_file.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\neteq.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\new_audio_conference_mixer.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\paced_sender.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\pcm16b.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\red.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\remote_bitrate_estimator.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\rent_a_codec.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\rtp_rtcp.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\video_capture.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\video_capture_module.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\video_capture_module_internal_impl.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\video_processing.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\video_processing_sse2.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\webrtc_h264.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\webrtc_i420.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\webrtc_opus.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\webrtc_utility.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\webrtc_video_coding.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\video_coding\\codecs\\vp8\\webrtc_vp8.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\video_coding\\codecs\\vp9\\webrtc_vp9.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\modules\\video_coding\\utility\\video_coding_utility.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\p2p\\libstunprober.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\p2p\\rtc_p2p.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\pc\\rtc_pc.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\system_wrappers\\field_trial_default.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\system_wrappers\\metrics_default.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\system_wrappers\\system_wrappers.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\tools\\command_line_parser.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\tools\\frame_editing_lib.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\tools\\video_quality_analysis.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\voice_engine\\level_indicator.lib
  ${WEBRTCBUILD}\\obj\\webrtc\\voice_engine\\voice_engine.lib
)
